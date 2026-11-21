/* -------------------------------------------------------------------
 *  @doc
 *  @notice Template file apch.h
 *
 *  @copyright Arboreus (http://arboreus.systems)
 *  @author Alexandr Kirilov (http://alexandr.kirilov.me)
 *  @created 21/09/2026 at 20:33:09
 * */// --------------------------------------------------------------

#ifndef APRIVATE_H_PCH
#define APRIVATE_H_PCH

#if defined __cplusplus

#pragma once

// System includes
#include <QObject>
#include <QByteArray>
#include <QByteArrayView>
#include <QMetaType>
#include <QString>
#include <QVariant>
#include <QtCore/qglobal.h>
#include <cstddef>
#include <string.h>
#include <limits>
#include <sys/mman.h>
#include <sys/resource.h>
#include <unistd.h>

//Android includes
#ifdef Q_OS_ANDROID
#include <QtCore/private/qandroidextras_p.h>
#include <QJniObject>
#endif

// Application includes

// Constants and defintions

// Namespace

#endif // defined __cplusplus

#endif // APRIVATE_H_PCH
