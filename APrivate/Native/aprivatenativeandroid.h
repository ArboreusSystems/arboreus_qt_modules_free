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
#ifndef APRIVATENATIVEANDROID_H
#define APRIVATENATIVEANDROID_H

// Precompiled includes
#include <aprivate_pch.h>

// System includes

// Application includes
#include <alogger.h>
#include <aprivatenative.h>

// Constants and definitions

// Namespace
namespace ARB {

// Class definitions
class APrivateNativeAndroid : public APrivateNative {

	Q_OBJECT

	public:

		explicit APrivateNativeAndroid(QObject* parent = nullptr);
		virtual ~APrivateNativeAndroid(void);

		virtual void mScreen(bool inMode) override;
};

} // namespace ARB

#endif // APRIVATENATIVEANDROID_H
