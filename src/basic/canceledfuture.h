/*
 *   Copyright (C) 2016 Ivan Cukic <ivan.cukic(at)kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2,
 *   or (at your option) any later version, as published by the Free
 *   Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef ASYNQT_CONS_CANCELED_FUTURE_H
#define ASYNQT_CONS_CANCELED_FUTURE_H

#include <asynqt/asynqt_export.h>

#include <QFuture>
#include <QFutureInterface>
#include <QObject>
#include <QTimer>

#include "../private/basic/canceledfuture_p.h"

namespace AsynQt {

template <typename _Result = void>
QFuture<_Result> makeCanceledFuture()
{
    using namespace detail;

    return (new CanceledFutureInterface<_Result>())->start();
}

} // namespace AsynQt

#endif // ASYNQT_CONS_CANCELED_FUTURE_H
