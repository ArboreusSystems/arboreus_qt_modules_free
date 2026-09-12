// ----------------------------------------------------------
/*!
	\headerfile AUIConfig
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 18/02/2026 at 09:10:27
	\endlist
*/
// ----------------------------------------------------------
#ifndef AUICONFIG_H
#define AUICONFIG_H

// Precompiled includes
#include <auihandler_pch.h>

// System includes

// Application includes
#include <alogger.h>
#include <auihandlerconfig.h>

// Constants and definitions

// Namesapces
namespace ARB {

// Class definitions
class AUIConfig : public QObject {

	Q_OBJECT

	public:

		explicit AUIConfig(QObject* parent = nullptr);
		virtual ~AUIConfig(void);

		void mInit(AUIHandlerConfig* inConfig);

	public slots:

		int mUIWidth(void);
		int mUIHeight(void);
		int mDesktopUIWidth(void);
		int mDesktopUIHeight(void);

		int mFontSizeHeader(void);
		int mFontSizeRegular(void);
		int mFontSizeTextInput(void);

		int mBorderSize(void);
		int mRadius(void);
		int mElementHeight(void);

	private:

		AUIHandlerConfig* pConfig = nullptr;
};

} // namespace ARB

#endif // AUICONFIG_H
