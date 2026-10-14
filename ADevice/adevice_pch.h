/* -------------------------------------------------------------------
 *  @doc
 *  @notice Template file apch.h
 *
 *  @copyright Arboreus (http://arboreus.systems)
 *  @author Alexandr Kirilov (http://alexandr.kirilov.me)
 *  @created 11/02/2026 at 11:45:42
 * */// --------------------------------------------------------------

#ifndef ADEVICE_H_PCH
#define ADEVICE_H_PCH

#if defined __cplusplus

#pragma once

// System includes
#include <QObject>
#include <QScreen>
#include <QVariantMap>
#include <QGuiApplication>
#include <QScreen>
#include <QRectF>
#include <QInputMethod>
#include <QByteArray>

// MacOS includes
#if defined(Q_OS_MACOS)
#include <sys/types.h>
#include <sys/sysctl.h>
#endif

// Android includes
#if defined(Q_OS_ANDROID)
#include <QJniObject>
#include <QCoreApplication>
#endif

// Application includes

// Constants and defintions

// Namespace

#endif // defined __cplusplus

#endif // ADEVICE_H_PCH
