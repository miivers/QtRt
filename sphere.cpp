/*****************************************************************************
 * sphere.cpp: Sphere primitive class
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

#include <QtDebug>

#include "sphere.h"
#include <math.h>

Sphere::Sphere( qreal xPos, qreal yPos, qreal zPos, qreal rayon ) :
        Primitive( xPos, yPos, zPos , 0, 0, 0)
{
    m_color = Qt::red;
    m_rayon = rayon;
    m_name = "Sphere";
}

Sphere::~Sphere()
{

}

void Sphere::intersect( Ray& ray, IntersectionInfo& info )
{
    qreal a = pow( ray.direction().x(), 2 ) +
              pow( ray.direction().y(), 2 ) +
              pow( ray.direction().z(), 2 );
    qreal b = 2.0 * ( ray.origin().x() * ray.direction().x() +
                    ray.origin().y() * ray.direction().y() +
                    ray.origin().z() * ray.direction().z() );
    qreal c = pow( ray.origin().x(), 2 ) +
              pow( ray.origin().y(), 2 ) +
              pow( ray.origin().z(), 2 ) - pow( m_rayon, 2 );
    qreal delta = pow( b, 2 ) - 4.0 * a * c;
    if ( delta >= ZERO )
    {
        qreal distance1 = ( -b - sqrt( delta ) ) / ( 2.0 * a );
        qreal distance2 = ( -b + sqrt( delta ) ) / ( 2.0 * a );
        if ( distance1 > ZERO && distance1 < distance2 )
            info.distance = distance1;
        else
            info.distance = distance2;
        info.hit = true;
    }
    else
        info.hit = false;
}

QVector3D*  Sphere::normal( QVector3D* intersect )
{
    return new QVector3D( *intersect );
}
