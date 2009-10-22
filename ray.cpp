/*****************************************************************************
 * ray.cpp: Ray class
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


#include "ray.h"

#include "scene.h"

Ray::Ray() : m_origin( NULL ), m_direction( NULL )
{
}

Ray::Ray( QVector3D* origin, QVector3D* direction ) :
        m_origin( origin ), m_direction( direction )
{
}

Ray::~Ray()
{
    if ( m_origin )
        delete m_origin;
    if ( m_direction )
        delete m_direction;
}

void                Ray::setOrigin( QVector3D* origin )
{
    if ( m_origin )
        delete m_origin;
    m_origin = origin;
}

void                Ray::setDirection( QVector3D* direction )
{
    if ( m_direction )
        delete m_direction;
    m_direction = direction;
}

const QVector3D*    Ray::getOrigin() const
{
    return m_origin;
}

const QVector3D*    Ray::getDirection() const
{
    return m_direction;
}

Ray*                Ray::getRay( Scene* scene, qreal x, qreal y )
{
    Ray* ray = new Ray();
    ray->setOrigin( new QVector3D( *( scene->camera() ) ) );
    ray->setDirection( new QVector3D( scene->depth() + scene->camera()->x(),
                                      scene->XResolution() / 2 - x +
                                      scene->camera()->y(),
                                      scene->YResolution() / 2 - y +
                                      scene->camera()->z() ) );
    return ray;
}
