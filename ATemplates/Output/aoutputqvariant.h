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

		virtual ~AOutputQVariant(void) {

			mClear();
		}


		// -----------
		/*!
			\fn

			Doc.
		*/

		QVariantMap mToVariantMap(void) {

			QVariant oDetachedValue = pValue;
			if (oDetachedValue.canConvert<QString>()) {
				QString oStr = oDetachedValue.toString();
				oStr.detach();
				oDetachedValue = QVariant::fromValue(oStr);
			} else if (oDetachedValue.canConvert<QByteArray>()) {
				QByteArray oBytes = oDetachedValue.toByteArray();
				oBytes.detach();
				oDetachedValue = QVariant::fromValue(oBytes);
			} else if (oDetachedValue.canConvert<QVariantMap>()) {
				QVariantMap oMap = oDetachedValue.toMap();
				oMap.detach();
				oDetachedValue = QVariant::fromValue(oMap);
			} else if (oDetachedValue.canConvert<QVariantList>()) {
				QVariantList oList = oDetachedValue.toList();
				oList.detach();
				oDetachedValue = QVariant::fromValue(oList);
			}

			QVariantMap oResult = {};
			oResult.insert("pStatus",QVariant::fromValue(pStatus));
			oResult.insert("pCode",QVariant::fromValue(pCode));
			oResult.insert("pValue",oDetachedValue);

			return oResult;
		}


		// -----------
		/*!
			\fn

			Doc.
		*/

		QVariantList mToVariantList(void) {

			QVariant oDetachedValue = pValue;

			if (oDetachedValue.canConvert<QString>()) {
				QString oStr = oDetachedValue.toString();
				oStr.detach();
				oDetachedValue = QVariant::fromValue(oStr);
			} else if (oDetachedValue.canConvert<QByteArray>()) {
				QByteArray oBytes = oDetachedValue.toByteArray();
				oBytes.detach();
				oDetachedValue = QVariant::fromValue(oBytes);
			} else if (oDetachedValue.canConvert<QVariantMap>()) {
				QVariantMap oMap = oDetachedValue.toMap();
				oMap.detach();
				oDetachedValue = QVariant::fromValue(oMap);
			} else if (oDetachedValue.canConvert<QVariantList>()) {
				QVariantList oList = oDetachedValue.toList();
				oList.detach();
				oDetachedValue = QVariant::fromValue(oList);
			}

			QVariantList oResult = {};
			oResult.insert(0,QVariant::fromValue(pStatus));
			oResult.insert(1,QVariant::fromValue(pCode));
			oResult.insert(2,oDetachedValue);

			return oResult;
		}

	private:

		void mClear(void) {

			if (!pValue.isValid() || pValue.isNull()) return;

			if (pValue.canConvert<QString>()) {
				QString oStr = pValue.toString();
				if (!oStr.isEmpty()) {
					oStr.detach();
					QChar* oRawData = oStr.data();
					for (int i = 0; i < oStr.length(); ++i) oRawData[i] = QChar(0);
					oStr.clear();
					oStr.squeeze();
				}
			} else if (pValue.canConvert<QByteArray>()) {
				QByteArray oBytes = pValue.toByteArray();
				if (!oBytes.isEmpty()) {
					oBytes.detach();
					volatile char* oRawBytes = const_cast<volatile char*>(oBytes.constData());
					for (int i = 0; i < oBytes.size(); ++i) oRawBytes[i] = 0;
					oBytes.clear();
					oBytes.squeeze();
				}
			} else if (pValue.canConvert<QVariantMap>()) {
				QVariantMap oMap = pValue.toMap();
				oMap.clear();
			} else if (pValue.canConvert<QVariantList>()) {
				QVariantList oList = pValue.toList();
				oList.clear();
			}

			pValue = QVariant();
		}
};

} // namespace ARB

Q_DECLARE_METATYPE(ARB::AOutputQVariant)

#endif // AOUTPUTQVARIANT_H
