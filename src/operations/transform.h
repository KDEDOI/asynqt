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

#ifndef ASYNQT_BASE_TRANSFORM_H
#define ASYNQT_BASE_TRANSFORM_H

#include <QFuture>
#include <QFutureWatcher>

#include <type_traits>
#include <memory>

#include "../private/operations/transform_p.h"

namespace AsynQt {

template <typename _Transformation>
void transform(const QFuture<void> &future, _Transformation &&transormation);

/**
 * This method applies the specified transformation function to
 * the value stored in the given future. Since the value might not
 * yet be present, it returns a future that will contain the
 * transformed value as soon as the original future is finished.
 *
 * If the original future is canceled, the transformation function
 * will not be invoked, and the resulting future will also be canceled.
 *
 * Example:
 *
 * <code>
 *     QFuture<int> answer = meaningOfLife()
 *     // answer will eventually contain 42
 *
 *     QFuture<QString> text = transform(answer, toText)
 *     // text will eventually contain the result of toText(42)
 * </code>
 *
 * @arg future the future to transform
 * @arg transformation unary function to apply to the value in the future
 * @returns a future that will contain the transformed value
 */
template <typename _In, typename _Transformation>
QFuture<
    typename detail::TransformFutureInterface<_In, _Transformation>::result_type
    >
transform(const QFuture<_In> &future, _Transformation &&transormation)
{
    using namespace detail;

    return (new TransformFutureInterface<_In, _Transformation>(
                future, std::forward<_Transformation>(transormation)))
        ->start();
}

} // namespace AsynQt

#endif // ASYNQT_BASE_TRANSFORM_H

