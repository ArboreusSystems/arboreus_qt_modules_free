// ----------------------------------------------------------
/*!
	\headerfile %{CN}
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 20/10/2025 at 15:53:40
	\endlist
*/
// ----------------------------------------------------------

#ifndef AAPPLICATIONCONFIG_H
#define AAPPLICATIONCONFIG_H

// Precompiled includes
#include <aapplication_pch.h>

// System includes

// Application includes

// Constants and defintions

// Namespace
namespace ARB {

// Classes
class ABackend;

// Interface
class AApplicationConfig {

	public:


		// ------------------------
		// Application

		virtual QThread::Priority AApplicationConfig_Application_ThreadPriority(void) = 0;
		virtual QString AApplicationConfig_Application_Organisation(void) = 0;
		virtual QString AApplicationConfig_Application_Name(void) = 0;


		// ------------------------
		// Lifecycle

		virtual void AApplicationConfig_Lifecycle_WillLaunchBackend(void) = 0;
		virtual void AApplicationConfig_Lifecycle_DidLaunchBackend(void) = 0;
		virtual void AApplicationConfig_Lifecycle_WillLaunchUI(void) = 0;
		virtual void AApplicationConfig_Lifecycle_DidLaunchUI(void) = 0;
		virtual void AApplicationConfig_Lifecycle_WillQuit(void) = 0;


		// ------------------------
		// Delegate

#if defined(Q_OS_IOS)

		virtual void AApplicationConfig_IOSLifecycle_DidBecomeActive(void) = 0;
		virtual void AApplicationConfig_IOSLifecycle_WillResignActive(void) = 0;
		virtual void AApplicationConfig_IOSLifecycle_DidReceiveMemoryWarning(void) = 0;
		virtual void AApplicationConfig_IOSLifecycle_WillTerminate(void) = 0;
		virtual void AApplicationConfig_IOSLifecycle_SignificantTimeChange(void) = 0;
		virtual void AApplicationConfig_IOSLifecycle_DidRegisterForRemoteNotificationsWithDeviceToken(QByteArray inToken) = 0;
		virtual void AApplicationConfig_IOSLifecycle_DidFailToRegisterForRemoteNotificationsWithError(void) = 0;
		virtual void AApplicationConfig_IOSLifecycle_DidUpdateUserActivity(void) = 0;
		virtual void AApplicationConfig_IOSLifecycle_DidEnterBackground(void) = 0;
		virtual void AApplicationConfig_IOSLifecycle_WillEnterForeground(void) = 0;

#endif


		// ------------------------
		// Heartbeat

		virtual void AApplicationConfig_Heartbeat_OnBeat(void) = 0;
		virtual int AApplicationConfig_Heartbeat_DefaultTime(void) = 0;
		virtual bool AApplicationConfig_Heartbeat_DefaultAutostart(void) = 0;


		// ------------------------
		// Heartbeat

		virtual QVariantList AApplicationConfig_Translator_LocaleList(void) = 0;
		virtual QString AApplicationConfig_Translator_LocaleDefault(void) = 0;
		virtual QString AApplicationConfig_Translator_ResourceName(void) = 0;
};

} // namespace ARB

Q_DECLARE_INTERFACE(ARB::AApplicationConfig,"ARB::AApplicationConfig/1.0")

#endif // AAPPLICATIONCONFIG_H
