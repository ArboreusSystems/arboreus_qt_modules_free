// ----------------------------------------------------------
/*!
	\headerfile APrivateNative
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 21/09/2026 at 20:40:04
	\endlist
*/
// ----------------------------------------------------------
#ifndef APRIVATENATIVE_H
#define APRIVATENATIVE_H

// Precompiled includes
#include <aprivate_pch.h>

// System includes

// Application includes
#include <alogger.h>

// Namespace
namespace ARB {

// Class definitions
class APrivateNative : public QObject {

	Q_OBJECT

	public:

		explicit APrivateNative(QObject* parent = nullptr);
		virtual ~APrivateNative(void);

		virtual void mScreen(bool inMode);

	signals:

		void sgScreenshotTaken(void);
		void sgScreenRecordingChanged(bool isCaptured);
};

} // namespace ARB

#endif // APRIVATENATIVE_H
