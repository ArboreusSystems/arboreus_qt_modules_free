// ----------------------------------------------------------
/*!
	\headerfile ASecurity
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 21/09/2026 at 20:33:09
	\endlist
*/
// ----------------------------------------------------------

#ifndef APRIVACY_H
#define APRIVACY_H

// Precompiled includes
#include <aprivacy_pch.h>

// System includes

// Application includes
#include <alogger.h>
#include <aprivacynative.h>

// iOS includes
#ifdef Q_OS_IOS
#include <aprivacynativeios.h>
#endif

// Android includes
#ifdef Q_OS_ANDROID
#include <aprivacynativeandroid.h>
#endif

// Namespace
namespace ARB {

// Class definitions
class APrivacy : public QObject {

	Q_OBJECT

	public:

		explicit APrivacy(QObject* parent = nullptr);
		virtual ~APrivacy(void);

		void mInit(void);

	public slots:

		void mScreen(bool inMode);

	signals:

		void sgInitiated(void);

		void sgScreenshotTaken(void);
		void sgScreenRecordingChanged(bool inCaptured);

	private:

		APrivacyNative* pNative = nullptr;

	private slots:

		void slScreenshotTaken(void);
		void slScreenRecordingChanged(bool inCaptured);
};

} // namespace ARB

#endif // APRIVACY_H
