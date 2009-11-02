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
#include <QMatrix4x4>
#include <QColor>

#include "ray.h"
#include "IntersectionInfo.h"

#define ZERO    0.0000000001

class IntersectionInfo;

class Primitive
{
public:
    Primitive( qreal xPos, qreal yPos, qreal zPos,
               qreal xRotation, qreal yRotation, qreal zRotation );
    virtual ~Primitive();

    virtual void    intersect( Ray& ray, IntersectionInfo& info ) = 0;
    const QVector3D* position() { return m_position; }
    QColor          color() const { return m_color; }
    const QString   name() const { return m_name; }
    virtual QVector3D*      normal( QVector3D* intersect ) = 0;
    QMatrix4x4&     rotationMatrix();
protected:
    QVector3D*      m_position;
    QMatrix4x4*     m_rotationMatrix;
    QColor          m_color;
    QString         m_name;
};

#endif // PRIMITIVE_H
