// ----------------------------------------------------------
/*!
	\headerfile APrivate
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

#ifndef APRIVATE_H
#define APRIVATE_H

// Precompiled includes
#include <aprivate_pch.h>

// System includes

// Application includes
#include <alogger.h>
#include <aprivatenative.h>

// iOS includes
#ifdef Q_OS_IOS
#include <aprivatenativeios.h>
#endif

// Android includes
#ifdef Q_OS_ANDROID
#include <aprivatenativeandroid.h>
#endif


// Namespace
namespace ARB {

// Class definitions
class APrivate : public QObject {

	Q_OBJECT

	public:

		explicit APrivate(QObject* parent = nullptr);
		virtual ~APrivate(void);

		void mInit(void);

	public slots:

		void mScreen(bool inMode);

	signals:

		void sgInitiated(void);

		void sgScreenshotTaken(void);
		void sgScreenRecordingChanged(bool inCaptured);

	private:

		APrivateNative* pNative = nullptr;

	private slots:

		void slScreenshotTaken(void);
		void slScreenRecordingChanged(bool inCaptured);
};

} // namespace ARB

#endif // APRIVATE_H
