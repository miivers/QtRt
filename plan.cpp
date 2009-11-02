/*****************************************************************************
 * plan.cpp: Plan primitive class
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


#include "plan.h"

Plan::Plan( qreal xPos, qreal yPos, qreal zPos ) :
    Primitive( xPos, yPos, zPos, 0, 0, 0)
{
    m_color = QColor( Qt::blue );
    m_name  = "Plan";
}

void   Plan::intersect( Ray& ray, IntersectionInfo& info )
{
    if ( ray.direction().z() == 0.0 )
        info.hit = false;
    else
    {
        info.distance = - ray.origin().z() / ray.direction().z();
        info.hit = true;
    }
}

QVector3D*  Plan::normal( QVector3D* intersect )
{
    return new QVector3D( 0.0, 0.0, 100.0 );
}
