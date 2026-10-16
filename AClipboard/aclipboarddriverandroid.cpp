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

// Global variables
static std::atomic<uint64_t> g_oCurrentCopyTaskId{0};


// -----------
/*!
	\fn

	Doc.
*/

void fAClipboardDriverAndroid_TextCopyPrivate(QString& inText) {

	if (inText.isEmpty()) return;

	auto* oInterface = qApp->nativeInterface<QNativeInterface::QAndroidApplication>();
	if (!oInterface) {
		_A_WARNING << "Native Android application interface is unavailable";
		return;
	}

	const int oTextLength = inText.length();
	auto oBuffer = std::shared_ptr<ushort[]>(new ushort[oTextLength]);

	const QChar* rawData = inText.constData();
	for (int i = 0; i < oTextLength; ++i) {
		oBuffer[i] = rawData[i].unicode();
	}

	QChar* oOriginalData = inText.data();
	for (int i = 0; i < oTextLength; ++i) {
		oOriginalData[i] = QChar(0);
	}
	inText.clear();
	inText.squeeze();

	oInterface->runOnAndroidMainThread([oInterface,oBuffer,oTextLength]() {

		QJniObject oActivity = oInterface->context();
		if (!oActivity.isValid()) return;

		QJniEnvironment oEnvironment;
		if (oEnvironment->ExceptionCheck()) oEnvironment->ExceptionClear();

		{
			jstring oJavaString = oEnvironment->NewString(reinterpret_cast<const jchar*>(oBuffer.get()), oTextLength);
			QJniObject oJavaText(oJavaString);
			QJniObject oMimeType = QJniObject::fromString("text/plain");

			QJniObject oActionSend = QJniObject::getStaticObjectField(
				"android/content/Intent",
				"ACTION_SEND",
				"Ljava/lang/String;"
			);

			QJniObject oIntent(
				"android/content/Intent",
				"(Ljava/lang/String;)V",
				oActionSend.object()
			);
			if (oIntent.isValid()) {

				oIntent.callObjectMethod(
					"setType",
					"(Ljava/lang/String;)Landroid/content/Intent;",
					oMimeType.object()
				);

				jint flagNewTask = QJniObject::getStaticField<jint>("android/content/Intent","FLAG_ACTIVITY_NEW_TASK");
				oIntent.callObjectMethod("addFlags", "(I)Landroid/content/Intent;", flagNewTask);

				oIntent.callObjectMethod(
					"putExtra",
					"(Ljava/lang/String;Z)V",
					QJniObject::fromString("android.content.extra.IS_SENSITIVE").object(),
					true
				);

				QJniObject oExtraTextKey = QJniObject::getStaticObjectField(
					"android/content/Intent",
					"EXTRA_TEXT",
					"Ljava/lang/String;"
				);

				oIntent.callObjectMethod(
					"putExtra",
					"(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",
					oExtraTextKey.object(),
					oJavaText.object()
				);

				QJniObject oChooserTitle = QJniObject::fromString("Private text");

				QJniObject oChooserIntent = QJniObject::callStaticObjectMethod(
					"android/content/Intent",
					"createChooser",
					"(Landroid/content/Intent;Ljava/lang/CharSequence;)Landroid/content/Intent;",
					oIntent.object(),
					oChooserTitle.object()
				);

				if (oChooserIntent.isValid()) {
					oActivity.callMethod<void>("startActivity", "(Landroid/content/Intent;)V", oChooserIntent.object());
					_A_DEBUG << "Private text copied to clipboard";
				}
			}

			if (oJavaString) oEnvironment->DeleteLocalRef(oJavaString);
		}

		for (int i = 0; i < oTextLength; ++i) oBuffer[i] = 0;

		if (oEnvironment->ExceptionCheck()) oEnvironment->ExceptionClear();
	});
}


// -----------
/*!
	\fn

	Doc.
*/

void fAClipboardDriverAndroid_TextCopyPrivateAndClear(QString& inText, int inTimeSeconds) {

	if (inText.isEmpty()) return;

	auto* oInterface = qApp->nativeInterface<QNativeInterface::QAndroidApplication>();
	if (!oInterface) {
		_A_WARNING << "Native Android application interface is unavailable";
		return;
	}

	const uint64_t oAssignedTaskId = ++g_oCurrentCopyTaskId;

	const int oTextLength = inText.length();
	auto oBuffer = std::shared_ptr<ushort[]>(new ushort[oTextLength]);

	const QChar* rawData = inText.constData();
	for (int i = 0; i < oTextLength; ++i) {
		oBuffer[i] = rawData[i].unicode();
	}

	QChar* oOriginalData = inText.data();
	for (int i = 0; i < oTextLength; ++i) {
		oOriginalData[i] = QChar(0);
	}
	inText.clear();
	inText.squeeze();


	oInterface->runOnAndroidMainThread([oInterface, oBuffer, oTextLength, inTimeSeconds, oAssignedTaskId]() {

		if (oAssignedTaskId != g_oCurrentCopyTaskId.load()) {
			_A_DEBUG << "Stale copy task intercepted. Aborting execution sequence.";
			for (int i = 0; i < oTextLength; ++i) oBuffer[i] = 0;
			return;
		}

		QJniObject oActivity = oInterface->context();
		if (!oActivity.isValid()) return;

		QJniEnvironment oEnvironment;
		if (oEnvironment->ExceptionCheck()) oEnvironment->ExceptionClear();

		{
			jstring oJavaString = oEnvironment->NewString(reinterpret_cast<const jchar*>(oBuffer.get()), oTextLength);
			QJniObject oJavaText(oJavaString);
			QJniObject oMimeType = QJniObject::fromString("text/plain");

			QJniObject oActionSend = QJniObject::getStaticObjectField(
				"android/content/Intent", "ACTION_SEND", "Ljava/lang/String;"
			);

			QJniObject oIntent("android/content/Intent", "(Ljava/lang/String;)V", oActionSend.object());

			if (oIntent.isValid()) {
				oIntent.callObjectMethod("setType", "(Ljava/lang/String;)Landroid/content/Intent;", oMimeType.object());

				jint flagNewTask = QJniObject::getStaticField<jint>("android/content/Intent", "FLAG_ACTIVITY_NEW_TASK");
				oIntent.callObjectMethod("addFlags", "(I)Landroid/content/Intent;", flagNewTask);

				oIntent.callObjectMethod(
					"putExtra",
					"(Ljava/lang/String;Z)Landroid/content/Intent;",
					QJniObject::fromString("android.content.extra.IS_SENSITIVE").object(),
					static_cast<jboolean>(true)
				);

				jlong oCurrentTimeMillis = QJniObject::callStaticMethod<jlong>("java/lang/System", "currentTimeMillis", "()J");
				jlong oExpiryTimeMillis = oCurrentTimeMillis + (jlong)(inTimeSeconds * 1000);

				oIntent.callObjectMethod(
					"putExtra",
					"(Ljava/lang/String;J)Landroid/content/Intent;",
					QJniObject::fromString("android.content.extra.AUTO_CLEAR_TIMESTAMP").object(),
					oExpiryTimeMillis
				);

				QJniObject oExtraTextKey = QJniObject::getStaticObjectField(
					"android/content/Intent", "EXTRA_TEXT", "Ljava/lang/String;"
				);
				oIntent.callObjectMethod(
					"putExtra",
					"(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",
					oExtraTextKey.object(),
					oJavaText.object()
				);

				QJniObject oChooserTitle = QJniObject::fromString("Private text");
				QJniObject oChooserIntent = QJniObject::callStaticObjectMethod(
					"android/content/Intent",
					"createChooser",
					"(Landroid/content/Intent;Ljava/lang/CharSequence;)Landroid/content/Intent;",
					oIntent.object(),
					oChooserTitle.object()
				);

				if (oChooserIntent.isValid() && oAssignedTaskId == g_oCurrentCopyTaskId.load()) {
					oActivity.callMethod<void>("startActivity", "(Landroid/content/Intent;)V", oChooserIntent.object());
					_A_DEBUG << "Secure Intent dispatched with native system-enforced background auto-clear metadata.";
				}
			}

			if (oJavaString) oEnvironment->DeleteLocalRef(oJavaString);
		}

		for (int i = 0; i < oTextLength; ++i) oBuffer[i] = 0;

		if (oEnvironment->ExceptionCheck()) oEnvironment->ExceptionClear();
	});
}


// -----------
/*!
	\fn

	Doc.
*/

void fAClipboardDriverAndroid_Clear(void) {

	QString oText("Clipboard cleared");
	fAClipboardDriverAndroid_TextCopyPrivate(oText);
}


// -----------
/*!
	\fn

	Doc.
*/

void fAClipboardDriverAndroid_ClearAfter(int inTimeSeconds) {

	QString oText("Clipboard cleared");
	fAClipboardDriverAndroid_TextCopyPrivateAndClear(oText,inTimeSeconds);
}


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

void AClipboardDriverAndroid::mTextCopyPrivate(QString& inText) {

	fAClipboardDriverAndroid_TextCopyPrivate(inText);
}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboardDriverAndroid::mTextCopyPrivateAndClear(QString& inText, int inTimeoutSeconds) {

	fAClipboardDriverAndroid_TextCopyPrivateAndClear(inText,inTimeoutSeconds);
}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboardDriverAndroid::mClear(void) {

	fAClipboardDriverAndroid_Clear();
}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboardDriverAndroid::mClearAfter(int inTimeSeconds) {

	fAClipboardDriverAndroid_ClearAfter(inTimeSeconds);
}


// -----------
/*!
	\fn

	Doc.
*/

QString AClipboardDriverAndroid::mTextPaste(void) {

	QString oOutput = "";
	return oOutput;
}