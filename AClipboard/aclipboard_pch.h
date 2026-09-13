/* -------------------------------------------------------------------
 *  @doc
 *  @notice Template file apch.h
 *
 *  @copyright Arboreus (http://arboreus.systems)
 *  @author Alexandr Kirilov (http://alexandr.kirilov.me)
 *  @created 28/06/2026 at 11:19:05
 * */// --------------------------------------------------------------

#ifndef ACLIPBOARD_H_PCH
#define ACLIPBOARD_H_PCH

#if defined __cplusplus

#pragma once

// System includes
#include <QObject>
#include <QGuiApplication>
#include <QClipboard>
#include <QMimeData>
#include <QStringList>
#include <QTimer>

// Android includes
#if defined(Q_OS_ANDROID)
#include <QJniObject>
#endif

// Application includes

// Constants and defintions

// Namespace


#endif // defined __cplusplus

#endif // ACLIPBOARD_H_PCH
