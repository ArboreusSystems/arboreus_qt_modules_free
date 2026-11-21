// ----------------------------------------------------------
/*!
	\class ASecurityNativeIOS
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 21/09/2026 at 21:49:03
	\endlist
*/
// ----------------------------------------------------------


// -----------
// IOS part
// -----------

// Class header
#include "aprivatenativeios.h"

// iOS private includes
#include <aprivatenativeiosprivate.h>

// Namespace
using namespace ARB;

// Global variables
APrivateNativeIOSHandler* gAPrivateNativeIOSHandler = nullptr;
APrivateNativeIOS* gASPrivateNativeIOS = nullptr;

// Class definitions
@implementation APrivateNativeIOSHandler

+(instancetype) mInstance {

	static APrivateNativeIOSHandler* oInstance = nil;
	static dispatch_once_t oOnceToken;
	dispatch_once(&oOnceToken,^{
		oInstance = [[APrivateNativeIOSHandler alloc] init];
	});

	return oInstance;
}

-(instancetype) init {

	self = [super init];
	if (self) {

		NSNotificationCenter* oCenter = [NSNotificationCenter defaultCenter];

		[oCenter addObserver:self selector:@selector(mShowPrivacyScreen) name:UIApplicationWillResignActiveNotification object:nil];
		[oCenter addObserver:self selector:@selector(mShowPrivacyScreen) name:UIApplicationDidEnterBackgroundNotification object:nil];
		[oCenter addObserver:self selector:@selector(mHidePrivateScreen) name:UIApplicationDidBecomeActiveNotification object:nil];
		[oCenter addObserver:self selector:@selector(mOnScreenshotDetected) name:UIApplicationUserDidTakeScreenshotNotification object:nil];
		[oCenter addObserver:self selector:@selector(mOnScreenRecordingChanged) name:UIScreenCapturedDidChangeNotification object:nil];

		[self setPAction:YES];
	}

	return self;
}

-(UIWindow*) mActiveWindow {

	for (UIScene* oScene in [UIApplication sharedApplication].connectedScenes) {

		if ([oScene isKindOfClass:[UIWindowScene class]]) {

			UIWindowScene* oWindowScene = (UIWindowScene*)oScene;
			for (UIWindow* oWwindow in oWindowScene.windows) {
				if (oWwindow.isKeyWindow) return oWwindow;
			}

			if (oWindowScene.windows.count > 0) return oWindowScene.windows.firstObject;
		}
	}

	return nil;
}

-(void) mShowPrivacyScreen {

	if ([self pAction]) {

		dispatch_async(dispatch_get_main_queue(), ^{

			UIWindow* oWindow = [self mActiveWindow];
			if (!oWindow) return;

			if (!self.pPrivateScreen) {

				UIBlurEffect* oBlur = [UIBlurEffect effectWithStyle:UIBlurEffectStyleDark];
				UIVisualEffectView* oBlurView = [[UIVisualEffectView alloc] initWithEffect:oBlur];
				[oBlurView setFrame:oWindow.bounds];
				[oBlurView setAutoresizingMask:
					UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight
				];

				UILabel* oLabel = [[UILabel alloc] init];
				[oLabel setText:@"Data Modifier"];
				[oLabel setTextColor:[UIColor whiteColor]];
				[oLabel setFont:[UIFont boldSystemFontOfSize:20]];
				[oLabel sizeToFit];
				[oLabel setCenter:oBlurView.contentView.center];
				[oLabel setAutoresizingMask:
					UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleRightMargin |
					UIViewAutoresizingFlexibleTopMargin | UIViewAutoresizingFlexibleBottomMargin
				];

				[oBlurView.contentView addSubview:oLabel];
				[self setPPrivateScreen:oBlurView];
			}

			[oWindow addSubview:self.pPrivateScreen];
			[oWindow bringSubviewToFront:self.pPrivateScreen];
			[oWindow layoutIfNeeded];
		});
	}
}

-(void) mHidePrivateScreen {

	if ([self pAction]) {

		dispatch_async(dispatch_get_main_queue(), ^{

			if (self.pPrivateScreen) {
				[self.pPrivateScreen removeFromSuperview];
				[self setPPrivateScreen:nil];
			}
		});
	}
}

-(void) mOnScreenshotDetected {

	if ([self pAction]) gASPrivateNativeIOS->mScreenshotTakenHandler();
}

-(void) mOnScreenRecordingChanged {

	if ([self pAction]) {
		if ([UIScreen mainScreen].isCaptured) {
			gASPrivateNativeIOS->mScreenRecordingHandler(true);
		} else {
			gASPrivateNativeIOS->mScreenRecordingHandler(false);
		}
	}
}

@end


// -----------
// Qt part
// -----------

QT_BEGIN_NAMESPACE

// -----------
/*!
	\fn

	Doc.
*/

APrivateNativeIOS::APrivateNativeIOS(QObject* parent) : APrivateNative(parent) {

	@autoreleasepool {
		gAPrivateNativeIOSHandler = [APrivateNativeIOSHandler mInstance];
		gASPrivateNativeIOS = this;
	}

	_A_DEBUG << "APrivateNativeIOS created";
}


// -----------
/*!
	\fn

	Doc.
*/

APrivateNativeIOS::~APrivateNativeIOS(void) {

	gAPrivateNativeIOSHandler = nullptr;
	gASPrivateNativeIOS = nullptr;

	_A_DEBUG << "APrivateNativeIOS deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivateNativeIOS::mScreen(bool inMode) {

	if (inMode) {
		[gAPrivateNativeIOSHandler setPAction: YES];
	} else {
		[gAPrivateNativeIOSHandler setPAction: NO];
	}
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivateNativeIOS::mScreenshotTakenHandler(void) {

	_A_DEBUG << "Screenshot taken";

	emit this->sgScreenshotTaken();
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivateNativeIOS::mScreenRecordingHandler(bool inCaptured) {

	_A_DEBUG << "Screen recording status changed" << inCaptured;

	emit this->sgScreenRecordingChanged(inCaptured);
}

QT_END_NAMESPACE
