cmake_minimum_required(VERSION 3.16)


## ----------------------------------------
## Global settings

set(A_NAME_TARGET AClipboard)
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
	aclipboard_pch.h
)

set(${A_PREFIX}_SOURCES_HEADERS
	${${A_PREFIX}_SOURCES_HEADERS}
	aclipboard.h
	aclipboarddriver.h
)

set(${A_PREFIX}_SOURCES_CPP
	${${A_PREFIX}_SOURCES_CPP}
	aclipboard.cpp
	aclipboarddriver.cpp
)

if(APPLE AND CMAKE_SYSTEM_NAME STREQUAL "Darwin")

	set(${A_PREFIX}_SOURCES_MACOS_HEADERS
		aclipboarddrivermacos.h
	)

	set(${A_PREFIX}_SOURCES_MACOS_CPP
		aclipboarddrivermacos.cpp
	)

	set(${A_PREFIX}_SOURCES
		${${A_PREFIX}_SOURCES}
		${${A_PREFIX}_SOURCES_MACOS_HEADERS}
		${${A_PREFIX}_SOURCES_MACOS_CPP}
	)

endif()

if(IOS)

	set(${A_PREFIX}_SOURCES_IOS_HEADERS
		aclipboarddriverios.h
		aclipboarddriveriosnative.h
	)

	set(${A_PREFIX}_SOURCES_IOS_OBJ_CPP
		aclipboarddriverios.mm
	)

	set(${A_PREFIX}_SOURCES
		${${A_PREFIX}_SOURCES}
		${${A_PREFIX}_SOURCES_IOS_HEADERS}
		${${A_PREFIX}_SOURCES_IOS_OBJ_CPP}
	)

endif()

if(ANDROID)

	set(${A_PREFIX}_SOURCES_ANDROID_HEADERS
		aclipboarddriverandroid.h
	)

	set(${A_PREFIX}_SOURCES_ANDROID_CPP
		aclipboarddriverandroid.cpp
	)

	set(${A_PREFIX}_SOURCES
		${${A_PREFIX}_SOURCES}
		${${A_PREFIX}_SOURCES_ANDROID_HEADERS}
		${${A_PREFIX}_SOURCES_ANDROID_CPP}
	)

endif()

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
)


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

if(IOS)

	target_link_libraries(${A_NAME_TARGET}
		PRIVATE
			"-framework Foundation"
			"-framework UIKit"
	)

endif()

target_compile_definitions(${A_NAME_TARGET}
	PRIVATE
		ACLIPBOARD_LIBRARY
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
