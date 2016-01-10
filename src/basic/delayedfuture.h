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

#ifndef ASYNQT_CONS_DELAYED_FUTURE_H
#define ASYNQT_CONS_DELAYED_FUTURE_H

#include <asynqt/asynqt_export.h>

#include <QFuture>
#include <QFutureInterface>
#include <QObject>
#include <QTimer>

#include "../private/basic/delayedfuture_p.h"

namespace AsynQt {

template <typename _Result>
QFuture<_Result> makeDelayedFuture(_Result &&value, int milliseconds)
{
    using namespace detail;

    return (new DelayedFutureInterface<_Result>(std::forward<_Result>(value),
                                                milliseconds))
        ->start();
}

ASYNQT_EXPORT
QFuture<void> makeDelayedFuture(int milliseconds);

} // namespace AsynQt

#ifndef ASYNQT_DISABLE_STD_CHRONO

#include <chrono>

namespace AsynQt {

template <typename _Result, typename Rep, typename Period>
QFuture<_Result> makeDelayedFuture(_Result &&value,
                                   std::chrono::duration<Rep, Period> duration)
{
    using namespace std::chrono;

    return makeDelayedFuture(std::forward<_Result>(value),
                             duration_cast<milliseconds>(duration).count());
}

template <typename Rep, typename Period>
QFuture<void> makeDelayedFuture(std::chrono::duration<Rep, Period> duration)
{
    using namespace std::chrono;

    return makeDelayedFuture(duration_cast<milliseconds>(duration).count());
}

} // namespace AsynQt

#endif // ASYNQT_DISABLE_STD_CHRONO


#endif // ASYNQT_CONS_DELAYED_FUTURE_H
