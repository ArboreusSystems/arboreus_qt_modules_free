// ----------------------------------------------------------
/*!
	\headerfile AFile
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 04/03/2022 at 16:36:45
	\endlist
*/
// ----------------------------------------------------------

#ifndef AFILE_H
#define AFILE_H

// Precompiled includes
#include <auniversal_pch.h>

// System includes

// Application includes
#include <auniversaldatamodels.h>

// Constants and definitions

// Namespace
namespace ARB {

// Class definitions
class AFile : public QObject {

	Q_OBJECT

	public:

		explicit AFile(QObject* parent = nullptr);
		virtual ~AFile(void);

		static bool mRemove(QString inPath);
		static bool mExist(QString inPath);
		static bool mEncodeBase64(QString inPath,QByteArray inDatumn);
		static AFileReply mDecodeBase64(QString inPath);
};

} // namespace ARB

#endif // AFILE_H
