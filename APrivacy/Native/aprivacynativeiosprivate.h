// ----------------------------------------------------------
/*!
    \headerfile %{CN}
    \title
    \brief Template file files/cppheader/file.h

    \list
    \li @notice Template file classes/file.h
    \li @copyright Arboreus (http://arboreus.systems)
    \li @author Alexandr Kirilov (http://alexandr.kirilov.me)
    \li @created 23/09/2026 at 13:49:43
    \endlist
*/
// ----------------------------------------------------------

#ifndef APRIVACYNATIVEIOSPRIVATE_H
#define APRIVACYNATIVEIOSPRIVATE_H

// Precompiled includes

// System includes

// iOS includes
#import <UIKit/UIKit.h>

// Application includes

// Constants and defintions

// Class definitions
@interface APrivacyNativeIOSHandler : NSObject

	@property (nonatomic, strong) UIView* pPrivacyScreen;
	@property (nonatomic,assign) BOOL pAction;

@end

#endif // APRIVACYNATIVEIOSPRIVATE_H
