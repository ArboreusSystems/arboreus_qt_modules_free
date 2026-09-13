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

void AClipboardDriverIOS::mTextCopySensitiveTo(QString inText) {

	NSString* oNSText = inText.toNSString();
	UIPasteboard* oPasteboard = [UIPasteboard generalPasteboard];
    
	NSMutableDictionary* oOptions = [[NSMutableDictionary alloc] init];
	[oOptions setObject:@YES forKey:@"UIPasteboardOptionLocalOnly"];
	[oOptions setObject:@YES forKey:@"UIPasteboardOptionSensitive"];

	if ([oPasteboard respondsToSelector:@selector(setString:options:)]) {
		void(*setStringWithOptions)(id,SEL,NSString*,NSDictionary*) = (void(*)(id,SEL,NSString*,NSDictionary*))[oPasteboard methodForSelector:@selector(setString:options:)];
		setStringWithOptions(oPasteboard,@selector(setString:options:),oNSText,oOptions);
	} else {
		oPasteboard.string = oNSText;
	}
}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboardDriverIOS::mClear(void) {

	[UIPasteboard generalPasteboard].items = @[];

	_A_DEBUG << "Clipboard cleared";
}

QT_END_NAMESPACE
