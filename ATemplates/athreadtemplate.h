// ----------------------------------------------------------
/*!
	\headerfile %{CN}
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://kirilov.me)
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

template <typename TServiceTemplate>
class AThreadTemplate : public QThread {

	static_assert(
		std::is_base_of_v<QObject,TServiceTemplate>,
		"ServiceTemplate must derive from QObject"
	);

	Q_DISABLE_COPY_MOVE(AThreadTemplate)

	public:

		explicit AThreadTemplate(
			TServiceTemplate* inService,
			QObject* parent = nullptr,
			QThread::Priority inPriority = QThread::InheritPriority
		) : QThread(parent) {

			mConstruct(inService);
			this->start(inPriority);
		}

		explicit AThreadTemplate(
			TServiceTemplate* inService,
			const std::function<void(TServiceTemplate*)>& inOnBoundCallback,
			QObject* parent = nullptr,
			QThread::Priority inPriority = QThread::InheritPriority
		) : QThread(parent) {

			mConstruct(inService);
			if (inOnBoundCallback) inOnBoundCallback(inService);
			this->start(inPriority);
		}

		virtual ~AThreadTemplate(void) {

			this->mResume();

			if constexpr (std::is_base_of_v<AThreadServiceTemplate,TServiceTemplate>) {
				if (pService != nullptr && this->isRunning()) {
					QMetaObject::invokeMethod(
						static_cast<AThreadServiceTemplate*>(pService.data()),
						&AThreadServiceTemplate::slHandleStopping,
						Qt::QueuedConnection
					);
				}
			}

			this->quit();
			this->wait();
		}

		TServiceTemplate* mService(void) const {

			return pService.data();
		}

		void mSuspend(void) {

			if (!this->isRunning()) return;

			if constexpr (std::is_base_of_v<AThreadServiceTemplate,TServiceTemplate>) {
				if (pService != nullptr) pService->mSuspend();
			}
		}

		void mResume(void) {

			if constexpr (std::is_base_of_v<AThreadServiceTemplate,TServiceTemplate>) {
				if (pService != nullptr) pService->mResume();
			}
		}

	protected:

		void run(void) override {

			QThread::run();
		}

	private:

		QPointer<TServiceTemplate> pService = nullptr;

		void mConstruct(TServiceTemplate* inService) {

			Q_ASSERT_X(inService != nullptr,"AThreadTemplate","inService must not be null");
			Q_ASSERT_X(inService->parent() == nullptr,"AThreadTemplate","inService must not have a parent");

			pService = inService;
			pService->moveToThread(this);

			if constexpr (std::is_base_of_v<AThreadServiceTemplate,TServiceTemplate>) {
				QObject::connect(
					this,&QThread::started,
					static_cast<AThreadServiceTemplate*>(inService),&AThreadServiceTemplate::slHandleStarted
				);
			}

			QObject::connect(
				this,&QThread::finished,
				inService,&QObject::deleteLater
			);
		}
};

} // namespace ARB

#endif // ATHREADTEMPLATE_H
