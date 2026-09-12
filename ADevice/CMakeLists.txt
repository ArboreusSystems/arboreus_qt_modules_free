cmake_minimum_required(VERSION 3.16)


## ----------------------------------------
## Global settings

set(A_NAME_TARGET ADevice)
set(A_PREFIX A_${A_NAME_TARGET})


## ----------------------------------------
## Project settings

project(${A_NAME_TARGET} LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(A_OPTION_USING_PCH "${A_NAME_TARGET} using PCH support" ON)


## ----------------------------------------
## Library variables

set(${A_PREFIX}_DIR_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(${A_PREFIX}_SOURCES)
set(${A_PREFIX}_SOURCES_PRECOMPILED_HEADERS_PUBLIC)
set(${A_PREFIX}_SOURCES_PRECOMPILED_HEADERS_PRIVATE)
set(${A_PREFIX}_SOURCES_HEADERS)
set(${A_PREFIX}_SOURCES_CPP)
set(${A_PREFIX}_SOURCES_RESOURCES)

set(${A_PREFIX}_INCLUDE_DIR_PUBLIC)
set(${A_PREFIX}_INCLUDE_DIR_PRIVATE)


## ----------------------------------------
## Library sources

set(${A_PREFIX}_SOURCES_PRECOMPILED_HEADERS_PUBLIC
	${${A_PREFIX}_SOURCES_PRECOMPILED_HEADERS_PUBLIC}
	adevice_pch.h
)

set(${A_PREFIX}_SOURCES_HEADERS
	${${A_PREFIX}_SOURCES_HEADERS}
	adevice.h
	adeviceconfig.h
	adevicedatamodels.h
	adevicemetatypes.h
	akeyboard.h
	Native/adevicenative.h
	Enums/aenumdevicetype.h
	Enums/aenumplatform.h
	Enums/aenumstatusbarstyle.h
)

set(${A_PREFIX}_SOURCES_CPP
	${${A_PREFIX}_SOURCES_CPP}
	adevice.cpp
	adevicemetatypes.cpp
	akeyboard.cpp
	Native/adevicenative.cpp
)

set(${A_PREFIX}_SOURCES
	${${A_PREFIX}_SOURCES}
	${${A_PREFIX}_SOURCES_PRECOMPILED_HEADERS_PRIVATE}
	${${A_PREFIX}_SOURCES_PRECOMPILED_HEADERS_PUBLIC}
	${${A_PREFIX}_SOURCES_HEADERS}
	${${A_PREFIX}_SOURCES_CPP}
	${${A_PREFIX}_SOURCES_RESOURCES}
)

set(${A_PREFIX}_INCLUDE_DIR_PUBLIC
	${${A_PREFIX}_INCLUDE_DIR_PUBLIC}
	${${A_PREFIX}_DIR_ROOT}
	${${A_PREFIX}_DIR_ROOT}/Enums
	${${A_PREFIX}_DIR_ROOT}/Native
)


## ----------------------------------------
## Platforms settings

if(APPLE)

	enable_language(OBJC OBJCXX Swift)

endif()

if(IOS)

	enable_language(OBJC OBJCXX Swift)

	set(${A_PREFIX}_SOURCES_IOS_OBJC_HEADERS
		Native/adevicenativeios.h
		Native/adevicenativeioshandler.h
	)

	set(${A_PREFIX}_SOURCES_IOS_OBJC
		Native/adevicenativeios.mm
	)

	set(${A_PREFIX}_SOURCES
		${${A_PREFIX}_SOURCES}
		${${A_PREFIX}_SOURCES_IOS_OBJC_HEADERS}
		${${A_PREFIX}_SOURCES_IOS_OBJC}
	)

endif()

if(ANDROID)

	set(QT_FORCE_CMP0156_TO_VALUE NEW)

	set(${A_PREFIX}_SOURCES_ANDROID_HEADERS
		Native/adevicenativeandroid.h
	)

	set(${A_PREFIX}_SOURCES_ANDROID_CPP
		Native/adevicenativeandroid.cpp
	)

	set(${A_PREFIX}_SOURCES
		${${A_PREFIX}_SOURCES}
		${${A_PREFIX}_SOURCES_ANDROID_HEADERS}
		${${A_PREFIX}_SOURCES_ANDROID_CPP}
	)

endif()


## ----------------------------------------
## Qt settings


find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)
qt_add_library(${A_NAME_TARGET} STATIC ${${A_PREFIX}_SOURCES})

target_link_libraries(${A_NAME_TARGET}
	PRIVATE
		Qt6::Quick
	PUBLIC
		ALogger
)

target_compile_definitions(${A_NAME_TARGET}
	PRIVATE
		ADEVICE_LIBRARY
)

target_include_directories(${A_NAME_TARGET}
	PUBLIC ${${A_PREFIX}_INCLUDE_DIR_PUBLIC}
	PRIVATE ${${A_PREFIX}_INCLUDE_DIR_PRIVATE}
)


## ----------------------------------------
## Precompiled headers settings

if(
	NOT ${${A_PREFIX}_SOURCES_PRECOMPILED_HEADERS_PRIVATE} EQUAL "" OR
	NOT ${${A_PREFIX}_SOURCES_PRECOMPILED_HEADERS_PUBLIC} EQUAL ""
)
	if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.16 AND A_OPTION_USING_PCH)
		message(STATUS "Using PCH for ${A_NAME_TARGET}")
		target_precompile_headers(${A_NAME_TARGET}
			PRIVATE ${${A_PREFIX}_SOURCES_PRECOMPILED_HEADERS_PRIVATE}
			PUBLIC ${${A_PREFIX}_SOURCES_PRECOMPILED_HEADERS_PUBLIC}
		)
		set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
	else()
		message(STATUS "No PCH for ${A_NAME_TARGET}")
	endif()
endif()
