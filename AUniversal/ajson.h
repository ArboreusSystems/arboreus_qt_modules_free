// ----------------------------------------------------------
/*!
	\headerfile AJson
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 23/07/2021 at 19:31:23
	\endlist
*/
// ----------------------------------------------------------

#ifndef AJSON_H
#define AJSON_H

// Precompiled includes
#include <auniversal_pch.h>

// System includes

// Application includes
#include <auniversaldatamodels.h>
#include <auniversalmetatypes.h>

// Constants and definitions


// Namespace
namespace ARB {

// Class definitions
class AJson : public QObject {

	Q_OBJECT

	public:

		explicit AJson(QObject* parent = nullptr);
		virtual ~AJson(void);

		static bool mToBase64FileFromObject(QString inPath,QJsonObject inObject);
		static bool mToBase64FileFromMap(QString inPath,QVariantMap inMap);
		static bool mToBase64FileFromHash(QString inPath,QVariantHash inHash);
		static bool mToBase64FileFromDocument(QString inPath,QJsonDocument inDocument);
		static AJsonFileReply mFromBase64File(QString inPath);
		static bool mToFileFromObject(QString inPath,QJsonObject inObject);
		static bool mToFileFromMap(QString inPath,QVariantMap inMap);
		static bool mToFileFromHash(QString inPath,QVariantHash inHash);
		static bool mToFileFromDocument(QString inPath,QJsonDocument inDocument);
		static AJsonFileReply mFromFile(QString inPath);
};

} // namespace ARB

#endif // AJSON_H
