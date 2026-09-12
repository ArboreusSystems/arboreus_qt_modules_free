// ----------------------------------------------------------
/*!
	\headerfile %{CN}
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 15/10/2025 at 17:09:20
	\endlist
*/
// ----------------------------------------------------------

#ifndef ATHREADTEMPLATE_H
#define ATHREADTEMPLATE_H

// Precompiled includes
#include <atemplates_pch.h>

// System includes

// Application includes
#include <athreadservicetemplate.h>

// Constants and defintions

// Namespace
namespace ARB {

template <typename ServiceTemplate>
class AThreadTemplate: public QThread {

	public:

		explicit AThreadTemplate(ServiceTemplate* inService,QObject* parent = nullptr)
		: QThread(parent) {

			pService = inService;
			pService->moveToThread(this);

			this->start();
		}

		virtual ~AThreadTemplate(void) {

			this->quit();
			this->wait();
		}

		ServiceTemplate* mService(void) const {

			return pService;
		}

		void mSuspend(void) {

			auto oService = qobject_cast<AThreadServiceTemplate*>(pService);
			if (oService != nullptr) {
				oService->mSuspend();
			}
		}

		void mResume(void) {

			auto oService = qobject_cast<AThreadServiceTemplate*>(pService);
			if (oService != nullptr) {
				oService->mResume();
			}
		}

	protected:

		void run(void) override {

			QThread::run();
		}

	private:

		ServiceTemplate* pService = nullptr;
};

} // namespace ARB

#endif // ATHREADTEMPLATE_H
