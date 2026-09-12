// ----------------------------------------------------------
/*!
	\headerfile %{CN}
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
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

		explicit AThreadServiceTemplate(QObject* parent = nullptr): QObject(parent) {

			pMutex.lock();
		}

		virtual ~AThreadServiceTemplate(void) {

			pWaitCondition.wakeAll();
			pMutex.unlock();
		}

		void mResume(void) {

			pWaitCondition.wakeAll();
		}

		void mSuspend(void) {

			QMetaObject::invokeMethod(this,&AThreadServiceTemplate::slSuspend);
			pMutex.lock();
			pMutex.unlock();
		}

	private slots:

		void slSuspend(void) {

			pWaitCondition.wait(&pMutex);
		}

	private:

		QMutex pMutex;
		QWaitCondition pWaitCondition;
};

} // namespace ARB

#endif // ATHREADSERVICETEMPLATE_H
