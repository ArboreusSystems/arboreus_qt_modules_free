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

	if (inText.length() > 65536) inText = inText.left(65536);

	QJniEnvironment oEnvironment;
	if (!oEnvironment.isValid()) return;
	if (oEnvironment->PushLocalFrame(64) < 0) return;

	QJniObject oContext = QNativeInterface::QAndroidApplication::context();
	if (!oContext.isValid()) {
		oEnvironment->PopLocalFrame(nullptr);
		return;
	}

	QJniObject oClipboardString = QJniObject::getStaticObjectField(
		"android/content/Context",
		"CLIPBOARD_SERVICE",
		"Ljava/lang/String;"
	);
	QJniObject oClipboardManager = oContext.callObjectMethod(
		"getSystemService",
		"(Ljava/lang/String;)Ljava/lang/Object;",
		oClipboardString.object()
	);

	if (!oClipboardManager.isValid()) {
		oEnvironment->PopLocalFrame(nullptr);
		return;
	}

	QJniObject oJavaText = QJniObject::fromString(inText);
	QJniObject oJavaLabel = QJniObject::fromString("text");

	QJniObject oClippData = QJniObject::callStaticObjectMethod(
		"android/content/ClipData", "newPlainText",
		"(Ljava/lang/CharSequence;Ljava/lang/CharSequence;)Landroid/content/ClipData;",
		oJavaLabel.object(), oJavaText.object()
	);
	if (oClippData.isValid()) {

		QJniObject oClipDescription = oClippData.callObjectMethod("getDescription", "()Landroid/content/ClipDescription;");
		if (oClipDescription.isValid()) {

			QJniObject oExtras("android/os/PersistableBundle");

			QJniObject oExtraSensitiveKey = QJniObject::fromString("android.content.extra.IS_SENSITIVE");
			oExtras.callMethod<void>("putBoolean","(Ljava/lang/String;Z)V",oExtraSensitiveKey.object(),true);
			QJniObject oExcludeCloudKey = QJniObject::fromString("android.content.extra.EXCLUDE_FROM_CLOUD_SYNC");
			oExtras.callMethod<void>("putBoolean","(Ljava/lang/String;Z)V",oExcludeCloudKey.object(),true);

			QString oManufacturer = QJniObject::getStaticObjectField(
				"android/os/Build","MANUFACTURER","Ljava/lang/String;"
			).toString().toLower();

			if (oManufacturer.contains("samsung")) {

				QJniObject oSamsungKey = QJniObject::fromString("com.samsung.android.content.clipdata.IS_SENSITIVE");
				oExtras.callMethod<void>("putBoolean", "(Ljava/lang/String;Z)V", oSamsungKey.object(),true);
				QJniObject oSamsungCloudKey = QJniObject::fromString("com.samsung.android.content.clipdata.EXCLUDE_FROM_CLOUD_SYNC");
				oExtras.callMethod<void>("putBoolean", "(Ljava/lang/String;Z)V", oSamsungCloudKey.object(),true);

			} else if (oManufacturer.contains("oppo") || oManufacturer.contains("realme")) {

				QJniObject oOppoKey = QJniObject::fromString("com.oppo.clipboard.IS_SENSITIVE");
				oExtras.callMethod<void>("putBoolean","(Ljava/lang/String;Z)V",oOppoKey.object(),true);
				QJniObject oOppoPasswordKey = QJniObject::fromString("com.oppo.clipboard.is_password");
				oExtras.callMethod<void>("putBoolean","(Ljava/lang/String;Z)V",oOppoPasswordKey.object(),true);
				QJniObject oOppoCloudKey = QJniObject::fromString("com.oppo.clipboard.EXCLUDE_FROM_CLOUD_SYNC");
				oExtras.callMethod<void>("putBoolean","(Ljava/lang/String;Z)V",oOppoCloudKey.object(),true);

			} else if (oManufacturer.contains("honor") || oManufacturer.contains("huawei")) {

				QJniObject oHonorKey = QJniObject::fromString("com.hihonor.clipboard.IS_SENSITIVE");
				oExtras.callMethod<void>("putBoolean","(Ljava/lang/String;Z)V",oHonorKey.object(),true);
				QJniObject oHonorPasswordKey = QJniObject::fromString("com.hihonor.clipboard.is_password");
				oExtras.callMethod<void>("putBoolean","(Ljava/lang/String;Z)V",oHonorPasswordKey.object(),true);
			}

			oClipDescription.callMethod<void>("setExtras","(Landroid/os/PersistableBundle;)V",oExtras.object());
		}
	}

	if (oClippData.isValid()) {
		oClipboardManager.callMethod<void>(
			"setPrimaryClip",
			"(Landroid/content/ClipData;)V",
			oClippData.object()
		);
	}

	if (!inText.isEmpty()) {
		QChar* oRawData = inText.data();
		int oLength = inText.length();
		for (int i = 0; i < oLength; ++i) {
			oRawData[i] = QChar('\0');
		}
		inText.clear();
	}

	oEnvironment->PopLocalFrame(nullptr);
}


// -----------
/*!
	\fn

	Doc.
*/

void fAClipboardDriverAndroid_TextCopyPrivateAndClear(QString& inText, int inTimeSeconds = 30) {

	if (inText.length() > 65536) inText = inText.left(65536);

	QJniEnvironment oEnvironment;
	if (!oEnvironment.isValid()) return;
	if (oEnvironment->PushLocalFrame(64) < 0) return;

	QJniObject oContext = QNativeInterface::QAndroidApplication::context();
	if (!oContext.isValid()) {
		oEnvironment->PopLocalFrame(nullptr);
		return;
	}

	QJniObject oClipboardString = QJniObject::getStaticObjectField(
		"android/content/Context",
		"CLIPBOARD_SERVICE",
		"Ljava/lang/String;"
	);
	QJniObject oClipboardManager = oContext.callObjectMethod(
		"getSystemService",
		"(Ljava/lang/String;)Ljava/lang/Object;",
		oClipboardString.object()
	);

	if (!oClipboardManager.isValid()) {
		oEnvironment->PopLocalFrame(nullptr);
		return;
	}

	QJniObject oJavaText = QJniObject::fromString(inText);
	QJniObject oJavaLabel = QJniObject::fromString("password");

	QJniObject oClippData = QJniObject::callStaticObjectMethod(
		"android/content/ClipData", "newPlainText",
		"(Ljava/lang/CharSequence;Ljava/lang/CharSequence;)Landroid/content/ClipData;",
		oJavaLabel.object(), oJavaText.object()
	);
	if (oClippData.isValid()) {

		QJniObject oClipDescription = oClippData.callObjectMethod("getDescription", "()Landroid/content/ClipDescription;");
		if (oClipDescription.isValid()) {

			QJniObject oExtras("android/os/PersistableBundle");

			QJniObject oExtraSensitiveKey = QJniObject::fromString("android.content.extra.IS_SENSITIVE");
			oExtras.callMethod<void>("putBoolean","(Ljava/lang/String;Z)V",oExtraSensitiveKey.object(),true);
			QJniObject oExcludeCloudKey = QJniObject::fromString("android.content.extra.EXCLUDE_FROM_CLOUD_SYNC");
			oExtras.callMethod<void>("putBoolean","(Ljava/lang/String;Z)V",oExcludeCloudKey.object(),true);

			QString oManufacturer = QJniObject::getStaticObjectField(
				"android/os/Build","MANUFACTURER","Ljava/lang/String;"
			).toString().toLower();

			if (oManufacturer.contains("samsung")) {

				QJniObject oSamsungKey = QJniObject::fromString("com.samsung.android.content.clipdata.IS_SENSITIVE");
				oExtras.callMethod<void>("putBoolean", "(Ljava/lang/String;Z)V", oSamsungKey.object(),true);
				QJniObject oSamsungCloudKey = QJniObject::fromString("com.samsung.android.content.clipdata.EXCLUDE_FROM_CLOUD_SYNC");
				oExtras.callMethod<void>("putBoolean", "(Ljava/lang/String;Z)V", oSamsungCloudKey.object(),true);

			} else if (oManufacturer.contains("oppo") || oManufacturer.contains("realme")) {

				QJniObject oOppoKey = QJniObject::fromString("com.oppo.clipboard.IS_SENSITIVE");
				oExtras.callMethod<void>("putBoolean","(Ljava/lang/String;Z)V",oOppoKey.object(),true);
				QJniObject oOppoPasswordKey = QJniObject::fromString("com.oppo.clipboard.is_password");
				oExtras.callMethod<void>("putBoolean","(Ljava/lang/String;Z)V",oOppoPasswordKey.object(),true);
				QJniObject oOppoCloudKey = QJniObject::fromString("com.oppo.clipboard.EXCLUDE_FROM_CLOUD_SYNC");
				oExtras.callMethod<void>("putBoolean","(Ljava/lang/String;Z)V",oOppoCloudKey.object(),true);

			} else if (oManufacturer.contains("honor") || oManufacturer.contains("huawei")) {

				QJniObject oHonorKey = QJniObject::fromString("com.hihonor.clipboard.IS_SENSITIVE");
				oExtras.callMethod<void>("putBoolean","(Ljava/lang/String;Z)V",oHonorKey.object(),true);
				QJniObject oHonorPasswordKey = QJniObject::fromString("com.hihonor.clipboard.is_password");
				oExtras.callMethod<void>("putBoolean","(Ljava/lang/String;Z)V",oHonorPasswordKey.object(),true);
			}

			oClipDescription.callMethod<void>("setExtras","(Landroid/os/PersistableBundle;)V",oExtras.object());
		}
	}

	if (oClippData.isValid()) {
		oClipboardManager.callMethod<void>(
			"setPrimaryClip",
			"(Landroid/content/ClipData;)V",
			oClippData.object()
		);
	}

	if (inTimeSeconds > 0) {

		QJniObject oAlarmString = QJniObject::getStaticObjectField(
			"android/content/Context",
			"ALARM_SERVICE",
			"Ljava/lang/String;"
		);

		QJniObject oAlarmManager = oContext.callObjectMethod(
			"getSystemService",
			"(Ljava/lang/String;)Ljava/lang/Object;",
			oAlarmString.object()
		);
		if (oAlarmManager.isValid()) {

			QJniObject oIntent("android/content/Intent");
			QJniObject oActionString = QJniObject::fromString("com.myapp.ACTION_CLEAR_CLIPBOARD");
			oIntent.callObjectMethod("setAction", "(Ljava/lang/String;)Landroid/content/Intent;",oActionString.object());

			jint oPendingIntentFlagUpdate = 0x08000000;
			jint oPendingIntentFlagMutable = 0x02000000;
			jint oFlags = oPendingIntentFlagUpdate | oPendingIntentFlagMutable;

			QJniObject oPendingIntent = QJniObject::callStaticObjectMethod(
				"android/app/PendingIntent",
				"getBroadcast",
				"(Landroid/content/Context;ILandroid/content/Intent;I)Landroid/app/PendingIntent;",
				oContext.object(),
				static_cast<jint>(1001),
				oIntent.object(),
				oFlags
			);
			if (oPendingIntent.isValid()) {

				jlong oElapsedRealtime = QJniObject::callStaticMethod<jlong>("android/os/SystemClock","elapsedRealtime","()J");
				jlong oTriggerTime = oElapsedRealtime + (static_cast<jlong>(inTimeSeconds) * 1000);
				jint oAlarmTypeElapsedWakeup = 2;

				oAlarmManager.callMethod<void>(
					"setExactAndAllowWhileIdle",
					"(IJLandroid/app/PendingIntent;)V",
					oAlarmTypeElapsedWakeup,
					oTriggerTime,
					oPendingIntent.object()
				);
			}
		}
	}

	if (!inText.isEmpty()) {
		QChar* oRawData = inText.data();
		int oLength = inText.length();
		for (int i = 0; i < oLength; ++i) {
			oRawData[i] = QChar('\0');
		}
		inText.clear();
	}

	oEnvironment->PopLocalFrame(nullptr);
}


// -----------
/*!
	\fn

	Doc.
*/

void fAClipboardDriverAndroid_TextShare(QString& inText) {

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

void fAClipboardDriverAndroid_TextShareAndClear(QString& inText, int inTimeSeconds) {

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

void AClipboardDriverAndroid::mTextShare(QString& inText) {

	fAClipboardDriverAndroid_TextShare(inText);
}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboardDriverAndroid::mTextShareAndClear(QString& inText, int inTimeoutSeconds) {

	fAClipboardDriverAndroid_TextShareAndClear(inText,inTimeoutSeconds);
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

	QJniEnvironment env;
	if (!env.isValid() || env->PushLocalFrame(48) < 0) return QString();

	QJniObject ctx = QNativeInterface::QAndroidApplication::context();
	if (!ctx.isValid()) {
		env->PopLocalFrame(nullptr);
		return QString();
	}

	QJniObject clipString = QJniObject::getStaticObjectField("android/content/Context", "CLIPBOARD_SERVICE", "Ljava/lang/String;");
	QJniObject clipManager = ctx.callObjectMethod("getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;", clipString.object());
	if (!clipManager.isValid() || !clipManager.callMethod<jboolean>("hasPrimaryClip", "()Z")) {
		env->PopLocalFrame(nullptr);
		return QString();
	}

	bool isSensitive = false;
	QJniObject desc = clipManager.callObjectMethod("getPrimaryClipDescription", "()Landroid/content/ClipDescription;");
	if (desc.isValid()) {
		QJniObject extras = desc.callObjectMethod("getExtras", "()Landroid/os/PersistableBundle;");
		if (extras.isValid()) {
			jboolean s1 = extras.callMethod<jboolean>("getBoolean", "(Ljava/lang/String;)Z", QJniObject::fromString("android.content.extra.IS_SENSITIVE").object());
			jboolean s2 = extras.callMethod<jboolean>("getBoolean", "(Ljava/lang/String;)Z", QJniObject::fromString("com.samsung.android.content.clipdata.IS_SENSITIVE").object());
			if (s1 || s2) isSensitive = true;
		}
		QString label = desc.callObjectMethod("getLabel", "()Ljava/lang/CharSequence;").toString().toLower();
		if (label.contains("password") || label.contains("token") || label.contains("secret")) isSensitive = true;
	}

	QJniObject clipData = clipManager.callObjectMethod("getPrimaryClip", "()Landroid/content/ClipData;");
	if (!clipData.isValid() || clipData.callMethod<jint>("getItemCount", "()I") <= 0) {
		env->PopLocalFrame(nullptr);
		return QString();
	}

	QJniObject item = clipData.callObjectMethod("getItemAt", "(I)Landroid/content/ClipData$Item;", 0);
	if (!item.isValid()) {
		env->PopLocalFrame(nullptr);
		return QString();
	}

	// Safe plain text extraction
	QJniObject charSeq = item.callObjectMethod("coerceToText", "(Landroid/content/Context;)Ljava/lang/CharSequence;", ctx.object());
	QString rawResult = charSeq.isValid() ? charSeq.toString() : QString(); // Fixed the JNI signature crash via native .toString()

	// Enterprise mitigation & scrubbing
	int maxSafeLength = isSensitive ? 4096 : 65536;
	if (rawResult.length() > maxSafeLength) rawResult = rawResult.left(maxSafeLength);
	rawResult.remove(QRegularExpression("[\\x00-\\x1F\\x7F]")); // Remove control characters

	env->PopLocalFrame(nullptr);
	return rawResult.trimmed();
}