// ----------------------------------------------------------
/*!
	\headerfile %{CN}
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://kirilov.me)
	\li @created 15/10/2025 at 17:10:41
	\endlist
*/
// ----------------------------------------------------------

#ifndef ATHREADSERVICETEMPLATE_H
#define ATHREADSERVICETEMPLATE_H

// Precompiled includes
#include <atemplates_pch.h>

// System includes

// Application includes

// Constants and defintions

// Namespace
namespace ARB {

class AThreadServiceTemplate : public QObject {

	Q_OBJECT

	public:

		explicit AThreadServiceTemplate(QObject* parent = nullptr)	: QObject(parent) {}

		virtual ~AThreadServiceTemplate(void) {

			mResume();
		}

		void mResume(void) {

			QMutexLocker locker(&pMutex);
			pSuspended = false;
			pWaitCondition.wakeAll();
		}

		void mSuspend(void) {

			QMutexLocker locker(&pMutex);
			if (pSuspended) return;
			pSuspended = true;

			QMetaObject::invokeMethod(
				this,
				&AThreadServiceTemplate::slSuspend,
				Qt::QueuedConnection
			);

			while (pSuspended && !pIsSleeping) pStateCondition.wait(&pMutex);
		}

		bool mIsSuspended(void) const {

			QMutexLocker locker(&pMutex);
			return pIsSleeping;
		}

	public slots:

		void slHandleStarted(void) {

			mOnStarted();
		}

		void slHandleStopping(void) {

			mOnStopping();
		}

	protected:

		virtual void mOnStarted(void) {}
		virtual void mOnStopping(void) {}

	private slots:

		void slSuspend(void) {

			QMutexLocker locker(&pMutex);
			while (pSuspended) {
				pIsSleeping = true;
				pStateCondition.wakeAll();
				pWaitCondition.wait(&pMutex);
				pIsSleeping = false;
			}
		}

	private:

		mutable QMutex pMutex;
		QWaitCondition pWaitCondition;
		QWaitCondition pStateCondition;
		bool pSuspended = false;
		bool pIsSleeping = false;
};

} // namespace ARB

#endif // ATHREADSERVICETEMPLATE_H
