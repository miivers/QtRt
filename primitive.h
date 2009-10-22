/*****************************************************************************
 * primitive.h: Primitive Class
 *****************************************************************************
 * Copyright (C) 2008-2009
 *
 * Authors: Christophe Courtaut <christophe.courtaut@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/


#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <QVector3D>
#include <QColor>

#include "ray.h"

class Primitive
{
public:
    Primitive( qreal xPos, qreal yPos, qreal zPos );
    virtual ~Primitive();

    virtual qreal   intersect( Ray* ray ) = 0;
    QColor          getColor() const { return m_color; }
protected:
    QVector3D*      m_position;
    QColor          m_color;
};

#endif // PRIMITIVE_H
