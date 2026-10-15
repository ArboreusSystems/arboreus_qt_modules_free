// ----------------------------------------------------------
/*!
	\class AClipboardDriverIOS
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 13/09/2026 at 08:12:03
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "aclipboarddriverios.h"

// Class native header
#include <aclipboarddriveriosnative.h>


// -----------
// IOS part
// -----------


// -----------
// Qt part
// -----------

QT_BEGIN_NAMESPACE

// Namespace
using namespace ARB;

// Global variables
static UIBackgroundTaskIdentifier gBackgroundTask = UIBackgroundTaskInvalid;
static dispatch_block_t gPendingClearBlock = nil;


// -----------
/*!
	\fn

	Doc.
*/

void fAClipboardDriverIOS_TextCopyPrivate(QString& inText) {

	if (inText.isEmpty()) return;

	UIPasteboard* oPasteboard = [UIPasteboard generalPasteboard];

	@autoreleasepool {

		NSString* oNSText = [NSString stringWithCharacters:(const unichar*)inText.unicode() length:inText.length()];
		NSDate* oExpiryDate = [NSDate dateWithTimeIntervalSinceNow:300];

		NSDictionary* oOptions = @{
			UIPasteboardOptionLocalOnly: @YES,
			UIPasteboardOptionExpirationDate: oExpiryDate
		};

		NSArray* oItemsArray = @[@{@"public.utf8-plain-text": oNSText}];

		if ([oPasteboard respondsToSelector:@selector(setItems:options:)]) {
			@try {
				[oPasteboard setItems:oItemsArray options:oOptions];
				_A_DEBUG << "Copied private text securely";
			} @catch (NSException* oEexception) {
				_A_DEBUG << "Can't copy private text via advanced api: " << QString::fromUtf8([oEexception.reason UTF8String]);
				oPasteboard.string = oNSText;
			}
		} else {
			[oPasteboard setItems:oItemsArray options:oOptions];
		}
	}

	QChar* data = inText.data();
	for (int i = 0; i < inText.length(); ++i) {
		data[i] = QChar(0);
	}
	inText.clear();
	inText.squeeze();
}


// -----------
/*!
	\fn

	Doc.
*/

void fAClipboardDriverIOS_TextCopyPrivateAndClear(QString& inText,int inTimeSeconds) {

	fAClipboardDriverIOS_TextCopyPrivate(inText);
	fAClipboardDriverIOS_ClearAfter(inTimeSeconds);
}


// -----------
/*!
	\fn

	Doc.
*/

void fAClipboardDriverIOS_Clear(void) {

	dispatch_async(dispatch_get_main_queue(), ^{

		if (gPendingClearBlock != nil) {
			dispatch_block_cancel(gPendingClearBlock);
			gPendingClearBlock = nil;
			_A_DEBUG << "Clearing clipboard canceled for restarting";
		}

		NSDictionary* oOptions = @{UIPasteboardOptionExpirationDate: [NSDate date]};
		UIPasteboard* oPasteboard = [UIPasteboard generalPasteboard];
		[oPasteboard setItems:@[] options:oOptions];

		_A_DEBUG << "Clipboard cleared";

	});
}


// -----------
/*!
	\fn

	Doc.
*/

void fAClipboardDriverIOS_ClearAfter(int inTimeSeconds) {

	UIApplication* oApplication = [UIApplication sharedApplication];

	if (gBackgroundTask != UIBackgroundTaskInvalid) {
		[oApplication endBackgroundTask:gBackgroundTask];
		gBackgroundTask = UIBackgroundTaskInvalid;
	}

	if (gPendingClearBlock != nil) {
		dispatch_block_cancel(gPendingClearBlock);
		gPendingClearBlock = nil;
		_A_DEBUG << "Clearing clipboard canceled for restarting";
	}

	gBackgroundTask = [oApplication beginBackgroundTaskWithName:@"ClipboardClearTask" expirationHandler:^{
		if (gBackgroundTask != UIBackgroundTaskInvalid) {
			[oApplication endBackgroundTask:gBackgroundTask];
			gBackgroundTask = UIBackgroundTaskInvalid;
		}
	}];

	gPendingClearBlock = dispatch_block_create(DISPATCH_BLOCK_INHERIT_QOS_CLASS, ^{

		NSDictionary* oOptions = @{UIPasteboardOptionExpirationDate: [NSDate date]};
		UIPasteboard* oPasteboard = [UIPasteboard generalPasteboard];
		[oPasteboard setItems:@[] options:oOptions];

		if (gBackgroundTask != UIBackgroundTaskInvalid) {
			[oApplication endBackgroundTask:gBackgroundTask];
			gBackgroundTask = UIBackgroundTaskInvalid;
		}

		gPendingClearBlock = nil;

		_A_DEBUG << "Clipboard cleared";
	});

	dispatch_after(
		dispatch_time(DISPATCH_TIME_NOW, (int64_t)(inTimeSeconds * NSEC_PER_SEC)),
		dispatch_get_main_queue(),
		gPendingClearBlock
	);
}


// -----------
/*!
	\fn

	Doc.
*/

AClipboardDriverIOS::AClipboardDriverIOS(QObject* parent) : AClipboardDriver(parent) {

	_A_DEBUG << "ADeviceNativeIOS created";
}


// -----------
/*!
	\fn

	Doc.
*/

AClipboardDriverIOS::AClipboardDriverIOS(QClipboard* inClipboard, QObject* parent)
: AClipboardDriver(inClipboard,parent) {

	_A_DEBUG << "ADeviceNativeIOS created with clipboard";
}


// -----------
/*!
	\fn

	Doc.
*/

AClipboardDriverIOS::~AClipboardDriverIOS(void) {

	_A_DEBUG << "ADeviceNativeIOS deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboardDriverIOS::mTextCopyPrivate(QString inText) {

	fAClipboardDriverIOS_TextCopyPrivate(inText);
}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboardDriverIOS::mTextCopyPrivateAndClear(QString inText, int inTimeSeconds) {

	fAClipboardDriverIOS_TextCopyPrivateAndClear(inText,inTimeSeconds);
}



// -----------
/*!
	\fn

	Doc.
*/

void AClipboardDriverIOS::mClear(void) {

	fAClipboardDriverIOS_Clear();
}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboardDriverIOS::mClearAfter(int inTimeSeconds) {

	fAClipboardDriverIOS_ClearAfter(inTimeSeconds);
}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboardDriverIOS::mFlood(void) {

}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboardDriverIOS::mFloodAfter(int inTimeSeconds) {

}


// -----------
/*!
	\fn

	Doc.
*/

QString AClipboardDriverIOS::mTextPaste(void) {

	QString oOutput = "";

	UIPasteboard* pasteboard = [UIPasteboard generalPasteboard];
	if ([pasteboard containsPasteboardTypes:@[@"public.text"]]) {

		NSString* plainText = pasteboard.string;
		if (plainText) {
			_A_DEBUG << "Extracting standard plain text";
			oOutput = QString::fromNSString(plainText);
		}
	}

	return oOutput;
}

QT_END_NAMESPACE
