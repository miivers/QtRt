/*****************************************************************************
 * primitive.cpp: Primitive Class
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


#include "primitive.h"

#include <math.h>

Primitive::Primitive( qreal xPos, qreal yPos, qreal zPos,
                      qreal xRotation, qreal yRotation, qreal zRotation )
{
    m_position = new QVector3D( xPos, yPos, zPos );
    m_color = QColor(Qt::red);
    m_rotationMatrix = new QMatrix4x4();
    m_rotationMatrix->setIdentity();
    m_rotationMatrix->rotate( xRotation, 1.0, 0.0, 0.0 );
    m_rotationMatrix->rotate( yRotation, 0.0, 1.0, 0.0 );
    m_rotationMatrix->rotate( zRotation, 0.0, 0.0, 1.0 );
}

Primitive::~Primitive()
{
    delete m_position;
    delete m_rotationMatrix;
}

QVector3D*  Primitive::realOrigin( Ray* ray )
{
    return ( new QVector3D( ray->origin()->x() + m_position->x(),
                            ray->origin()->y() + m_position->y(),
                            ray->origin()->z() + m_position->z()) );
}

QMatrix4x4* Primitive::rotationMatrix()
{
    return m_rotationMatrix;
}
