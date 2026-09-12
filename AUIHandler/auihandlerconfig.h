// ----------------------------------------------------------
/*!
	\headerfile %{CN}
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 08/01/2026 at 21:57:50
	\endlist
*/
// ----------------------------------------------------------

#ifndef AUIHANDLERCONFIG_H
#define AUIHANDLERCONFIG_H

// Precompiled includes

// System includes

// Application includes

// Constants and defintions

// Namespace
namespace ARB {

// Class definition
class AUIHandlerConfig {

	public:

		virtual int AUIHandlerConfig_UIWidth(void) = 0;
		virtual int AUIHandlerConfig_UIHeight(void) = 0;
		virtual int AUIHandlerConfig_DesktopUIWidth(void) = 0;
		virtual int AUIHandlerConfig_DesktopUIHeight(void) = 0;

		virtual int AUIHandlerConfig_FontSizeHeader(void) = 0;
		virtual int AUIHandlerConfig_FontSizeRegular(void) = 0;
		virtual int AUIHandlerConfig_FontSizeTextInput(void) = 0;

		virtual int AUIHandlerConfig_BorderSize(void) = 0;
		virtual int AUIHandlerConfig_Radius(void) = 0;

		virtual int AUIHandlerConfig_ElementHeight(void) = 0;

		virtual QMap<QString,QString> AUIHandlerConfig_Colors(void) = 0;
		virtual QList<QString> AUIHandlerConfig_Fonts(void) = 0;
};

} // namespace ARB

Q_DECLARE_INTERFACE(ARB::AUIHandlerConfig,"ARB::AUIHandlerConfig/1.0")


#endif // AUIHANDLERCONFIG_H
