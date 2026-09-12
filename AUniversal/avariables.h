// ----------------------------------------------------------
/*!
	\headerfile AVariables
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 15/02/2026 at 10:07:39
	\endlist
*/
// ----------------------------------------------------------
#ifndef AVARIABLES_H
#define AVARIABLES_H

// Precompiled includes
#include <auniversal_pch.h>

// System includes

// Application includes

// Namesapces

// Constants and definitions

// Namespace
namespace ARB {

// Class definitions
class AVariables : public QObject {

	Q_OBJECT

	public:

		explicit AVariables(QObject* parent = nullptr);
		virtual ~AVariables(void);

		void mSetSignal(bool inSignal);

	public slots:

		QVariantMap mGetAll(void);
		QVariant mGet(QString inKey);
		QVariant mGetWithDefault(QString inKey, QVariant inDefault);
		void mSet(QString inKey, QVariant inVariable);

	signals:

		void sgUpdated(void);

	private:

		bool pSignal = false;
		QVariantMap pStorage = {};
};

} // namespace ARB

#endif // AVARIABLES_H
