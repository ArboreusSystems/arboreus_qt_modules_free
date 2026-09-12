// ----------------------------------------------------------
/*!
	\headerfile %{CN}
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 01/01/2026 at 16:29:50
	\endlist
*/
// ----------------------------------------------------------

#ifndef AOUTPUTQVARIANT_H
#define AOUTPUTQVARIANT_H

// Precompiled includes
#include <atemplates_pch.h>

// System includes

// Application includes
#include <auniversaldefinitions.h>

// Constants and defintions

// Namespace
namespace ARB {

class AOutputQVariant {

	public:

		_A_ENUM_STATUS pStatus = _A_ENUM_STATUS::Undefined;
		int pCode = 0;
		QVariant pValue = QVariant::fromValue(0);


		// -----------
		/*!
			\fn

			Doc.
		*/

		explicit AOutputQVariant(void) {}


		// -----------
		/*!
			\fn

			Doc.
		*/

		virtual ~AOutputQVariant(void) {}


		// -----------
		/*!
			\fn

			Doc.
		*/

		QVariantMap mToVariantMap(void) {

			QVariantMap oResult = {};
			oResult.insert("pStatus",QVariant::fromValue(pStatus));
			oResult.insert("pCode",QVariant::fromValue(pCode));
			oResult.insert("pValue",pValue);

			return oResult;
		}


		// -----------
		/*!
			\fn

			Doc.
		*/

		QVariantList mToVariantList(void) {

			QVariantList oResult = {};
			oResult.insert(0,QVariant::fromValue(pStatus));
			oResult.insert(1,QVariant::fromValue(pCode));
			oResult.insert(2,pValue);

			return oResult;
		}
};

} // namespace ARB

Q_DECLARE_METATYPE(ARB::AOutputQVariant)

#endif // AOUTPUTQVARIANT_H
