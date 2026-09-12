// ----------------------------------------------------------
/*!
	\headerfile ADir
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 16/10/2025 at 11:56:38
	\endlist
*/
// ----------------------------------------------------------
#ifndef ADIR_H
#define ADIR_H

// Precompiled includes
#include <auniversal_pch.h>

// System includes

// Application includes

// Namesapces

// Constants and definitions

//Namespace
namespace ARB {

// Class definition
class ADir : public QObject {

	Q_OBJECT

	public:

		explicit ADir(QObject* parent = nullptr);
		virtual ~ADir(void);

		static bool mEnsure(QString inPath);
		static bool mRemoveRecursively(QString inPath);
		static QStringList mGetSubdirs(QString inPath);
};

} // namespace ARB

#endif // ADIR_H
