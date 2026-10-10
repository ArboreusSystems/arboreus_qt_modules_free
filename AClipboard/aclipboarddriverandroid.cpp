// ----------------------------------------------------------
/*!
	\class AClipboardDriverAndroid
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 13/09/2026 at 08:11:34
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "aclipboarddriverandroid.h"

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

AClipboardDriverAndroid::AClipboardDriverAndroid(QObject* parent) : AClipboardDriver(parent) {

	_A_DEBUG << "AClipboardDriverAndroid created";
}


// -----------
/*!
	\fn

	Doc.
*/

AClipboardDriverAndroid::AClipboardDriverAndroid(QClipboard* inClipboard, QObject* parent)
: AClipboardDriver(inClipboard,parent) {

	_A_DEBUG << "AClipboardDriverAndroid created with with clipboard";
}


// -----------
/*!
	\fn

	Doc.
*/

AClipboardDriverAndroid::~AClipboardDriverAndroid() {

	_A_DEBUG << "AClipboardDriverAndroid deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboardDriverAndroid::mTextCopySensitiveTo(QString inText) {


	QNativeInterface::QAndroidApplication::runOnAndroidMainThread([inText]() {

		QJniObject oActivity = QNativeInterface::QAndroidApplication::context();
		if (!oActivity.isValid()) {
			_A_CRITICAL << "Can't get Android context";
			return;
		}

		QJniObject oService = QJniObject::fromString("clipboard");
		QJniObject oManager = oActivity.callObjectMethod(
			"getSystemService",
			"(Ljava/lang/String;)Ljava/lang/Object;",
			oService.object<jstring>()
		);
		if (!oManager.isValid()) {
			_A_CRITICAL << "Clipboard is invalid";
			return;
		}

		QJniObject oLabel = QJniObject::fromString("Sensitive Data");
		QJniObject oText = QJniObject::fromString(inText);

		QJniObject oClipData = QJniObject::callStaticObjectMethod(
			"android/content/ClipData",
			"newPlainText",
			"(Ljava/lang/CharSequence;Ljava/lang/CharSequence;)Landroid/content/ClipData;",
			oLabel.object<jobject>(),
			oText.object<jobject>()
		);
		if (!oClipData.isValid()) {
			_A_CRITICAL << "ClipData is invalid";
			return;
		}

		QJniObject oClipDescription = oClipData.callObjectMethod(
			"getDescription",
			"()Landroid/content/ClipDescription;"
		);
		if (oClipDescription.isValid()) {

			QJniObject oExtras("android/os/PersistableBundle");

			int oSDKVersion = QJniObject::getStaticField<jint>("android/os/Build$VERSION","SDK_INT");
			if (oSDKVersion >= 33) {

				QJniObject oExtraSensitiveKey = QJniObject::getStaticObjectField(
					"android/content/ClipDescription",
					"EXTRA_IS_SENSITIVE",
					"Ljava/lang/String;"
				);
				oExtras.callMethod<void>(
					"putBoolean",
					"(Ljava/lang/String;Z)V",
					oExtraSensitiveKey.object<jstring>(),
					true
				);

			} else {
				QJniObject oKey = QJniObject::fromString("android.content.extra.IS_SENSITIVE");
				oExtras.callMethod<void>(
					"putBoolean",
					"(Ljava/lang/String;Z)V",
					oKey.object<jstring>(),
					true
				);
			}

			// SAMSUNG ONE UI SPECIFIC FLAGS
			oExtras.callMethod<void>(
				"putBoolean",
				"(Ljava/lang/String;Z)V",
				QJniObject::fromString("com.samsung.android.content.extra.PRIVATE").object<jstring>(),
				true
			);
			oExtras.callMethod<void>(
				"putBoolean",
				"(Ljava/lang/String;Z)V",
				QJniObject::fromString("com.samsung.android.content.extra.IS_SENSITIVE").object<jstring>(),
				true
			);
			oExtras.callMethod<void>(
				"putBoolean",
				"(Ljava/lang/String;Z)V",
				QJniObject::fromString("is_password").object<jstring>(),
				true
			);

			// OPPO, REALME, ONEPLUS (ColorOS / Realme UI)
			oExtras.callMethod<void>(
				"putBoolean",
				"(Ljava/lang/String;Z)V",
				QJniObject::fromString("com.coloros.safecenter.clipboard.SENSITIVE").object<jstring>(),
				true
			);
			oExtras.callMethod<void>(
				"putBoolean",
				"(Ljava/lang/String;Z)V",
				QJniObject::fromString("oppo.content.extra.IS_SENSITIVE").object<jstring>(),
				true
			);

			// HONOR & HUAWEI (MagicOS / EMUI)
			oExtras.callMethod<void>(
				"putBoolean",
				"(Ljava/lang/String;Z)V",
				QJniObject::fromString("huawei.content.extra.IS_SENSITIVE").object<jstring>(),
				true
			);
			oExtras.callMethod<void>(
				"putBoolean",
				"(Ljava/lang/String;Z)V",
				QJniObject::fromString("com.huawei.secure.clipboard").object<jstring>(),
				true
			);

			// VIVO & IQOO (Funtouch OS / OriginOS)
			oExtras.callMethod<void>(
				"putBoolean",
				"(Ljava/lang/String;Z)V",
				QJniObject::fromString("com.vivo.clipboard.is_sensitive").object<jstring>(),
				true
			);

			oClipDescription.callMethod<void>(
				"setExtras",
				"(Landroid/os/PersistableBundle;)V",
				oExtras.object()
			);

			oManager.callMethod<void>(
				"setPrimaryClip",
				"(Landroid/content/ClipData;)V",
				oClipData.object()
			);

			_A_DEBUG << "Sensitive cross-vendor text copied securely";
		} else {
			_A_CRITICAL << "Clip description is invalid";
		}
	});
}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboardDriverAndroid::mClear(void) {

	QJniObject oContext = QNativeInterface::QAndroidApplication::context();
	if (oContext.isValid()) {

		QJniObject oString = QJniObject::getStaticObjectField(
			"android/content/Context",
			"CLIPBOARD_SERVICE",
			"Ljava/lang/String;"
		);

		QJniObject oManager = oContext.callObjectMethod(
			"getSystemService",
			"(Ljava/lang/String;)Ljava/lang/Object;",
			oString.object()
		);
		if (oManager.isValid()) {
			oManager.callMethod<void>("clearPrimaryClip","()V");
			_A_DEBUG << "Clipboard cleared";
		} else {
			_A_CRITICAL << "Manager is invalid";
		}

	} else {
		_A_CRITICAL << "Context is invalid";
	}
}
