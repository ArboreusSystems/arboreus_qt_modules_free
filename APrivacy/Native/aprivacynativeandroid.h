// ----------------------------------------------------------
/*!
	\headerfile ASecurityNativeAndroid
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 21/09/2026 at 21:48:32
	\endlist
*/
// ----------------------------------------------------------
#ifndef APRIVACYNATIVEANDROID_H
#define APRIVACYNATIVEANDROID_H

// Precompiled includes
#include <aprivacy_pch.h>

// System includes

// Application includes
#include <alogger.h>
#include <aprivacynative.h>

// Constants and definitions

// Namespace
namespace ARB {

// Class definitions
class APrivacyNativeAndroid : public APrivacyNative {

	Q_OBJECT

	public:

		explicit APrivacyNativeAndroid(QObject* parent = nullptr);
		virtual ~APrivacyNativeAndroid(void);

		virtual void mScreen(bool inMode) override;
};

} // namespace ARB

#endif // APRIVACYNATIVEANDROID_H
