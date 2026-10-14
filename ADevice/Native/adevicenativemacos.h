// ----------------------------------------------------------
/*!
	\headerfile ADeviceNativeMacOS
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 14/10/2026 at 18:11:48
	\endlist
*/
// ----------------------------------------------------------
#ifndef ADEVICENATIVEMACOS_H
#define ADEVICENATIVEMACOS_H

// Precompiled includes
#include <adevice_pch.h>

// System includes

// Application includes
#include <alogger.h>
#include <adevicenative.h>

// Constants and definitions

// Namespace
namespace ARB {

// Class definitions
class ADeviceNativeMacOS : public ADeviceNative {

	Q_OBJECT

	public:

		explicit ADeviceNativeMacOS(QObject* parent = nullptr);
		virtual ~ADeviceNativeMacOS(void);

		void mInit(void) override;

		QString mVendor(void) override;
		QString mBrand(void) override;
};

} // namespace ARB

#endif // ADEVICENATIVEMACOS_H
