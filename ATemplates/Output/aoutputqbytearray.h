// ----------------------------------------------------------
/*!
	\headerfile %{CN}
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 02/01/2026 at 11:30:16
	\endlist
*/
// ----------------------------------------------------------

#ifndef AOUTPUTQBYTEARRAY_H
#define AOUTPUTQBYTEARRAY_H

// Precompiled includes
#include <atemplates_pch.h>

// System includes

// Application includes
#include <auniversaldefinitions.h>

// Constants and defintions

// Namespace
namespace ARB {

class AOutputQByteArray {

	public:

		_A_ENUM_STATUS pStatus = _A_ENUM_STATUS::Undefined;
		int pCode = 0;
		QByteArray pValue = {};


		// -----------
		/*!
			\fn

			Doc.
		*/

		explicit AOutputQByteArray(void) {}


		// -----------
		/*!
			\fn

			Doc.
		*/

		virtual ~AOutputQByteArray(void) {}
};

} // namespace ARB

Q_DECLARE_METATYPE(ARB::AOutputQByteArray)

#endif // AOUTPUTQBYTEARRAY_H
