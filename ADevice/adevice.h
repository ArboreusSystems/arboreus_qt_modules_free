// ----------------------------------------------------------
/*!
	\headerfile ADevice
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 07/05/2021 at 18:44:46
	\endlist
*/
// ----------------------------------------------------------

#ifndef ADEVICE_H
#define ADEVICE_H

// Precompiled includes
#include <adevice_pch.h>

// System includes

// Application includes
#include <adeviceconfig.h>
#include <adevicedatamodels.h>
#include <adevicemetatypes.h>
#include <alogger.h>
#include <adevicenative.h>
#include <akeyboard.h>

// iOS includes
#ifdef Q_OS_IOS
#include <adevicenativeios.h>
#endif

// Android includes
#ifdef Q_OS_ANDROID
#include <adevicenativeandroid.h>
#endif

// Constants and definitions

// Global variables
extern QObject* gConfig;

// Namespace
namespace ARB {

// Classes
class ABackend;

// Class definitions
class ADevice : public QObject {

	Q_OBJECT

	public:

		AKeyboard* pKeyboard = nullptr;

		explicit ADevice(QObject* parent = nullptr);
		virtual ~ADevice(void);
		Q_DISABLE_COPY(ADevice)

		void mInit(void);

	public slots:

		_A_ENUM_DEVICE_TYPE mType(void);
		_A_ENUM_PLATFORM mPlatform(void);
		bool mIsLandscape(void);
		void mStatusBarStyle(ARB::AEnumStatusBarStyle::AStatusBarStyle inStyle);

	signals:

		void sgInitiated(void);
		void sgOrientationChanged(Qt::ScreenOrientation inOrientation);

	private:

		QScreen* pScreen = nullptr;
		ADeviceConfig* pConfig = nullptr;
		_A_ENUM_DEVICE_TYPE pType = _A_ENUM_DEVICE_TYPE::Undefined;
		_A_ENUM_PLATFORM pPlatform = _A_ENUM_PLATFORM::Undefined;
		ADeviceNative* pNative = nullptr;

	private slots:

		void slOrientationChanged(Qt::ScreenOrientation inOrientation);
};

} // namespace ARB

#endif // ADEVICE_H
