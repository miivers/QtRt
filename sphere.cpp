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
        Primitive( xPos, yPos, zPos )
{
    m_rayon = rayon;
}

Sphere::~Sphere()
{

}

qreal Sphere::intersect( Ray* ray )
{
    qreal a = pow( ray->getDirection()->x(), 2 ) +
              pow( ray->getDirection()->y(), 2 ) +
              pow( ray->getDirection()->z(), 2 );
    qreal b = 2 * ( ray->getOrigin()->x() * ray->getDirection()->x() +
                    ray->getOrigin()->y() * ray->getDirection()->y() +
                    ray->getOrigin()->z() * ray->getDirection()->z() );
    qreal c = pow( ray->getOrigin()->x(), 2 ) +
              pow( ray->getOrigin()->y(), 2 ) +
              pow( ray->getOrigin()->z(), 2 ) - pow( m_rayon, 2 );
    qreal delta = pow( b, 2 ) - 4 * a * c;
    if (delta < 0)
        return -1;
    qreal distance1 = (b * -1) - sqrt( delta ) / 2 * a;
    qreal distance2 = (b * -1) + sqrt( delta ) / 2 * a;
    return ( distance2 > distance1 && distance1 > 0 ? distance1 : distance2 );
}
