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

Ray::Ray() : m_origin( NULL ), m_realDirection( NULL ),m_direction( NULL )
{
}

Ray::Ray( QVector3D* origin, QVector3D* direction ) :
        m_origin( origin ), m_realDirection( direction )
{
    m_direction = new QVector3D();
}

Ray::~Ray()
{
    if ( m_origin )
        delete m_origin;
    if ( m_direction )
        delete m_direction;
    if ( m_realDirection )
        delete m_realDirection;
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

void                Ray::setRealDirection( QVector3D* direction )
{
    if ( m_realDirection )
        delete m_realDirection;
    m_realDirection = direction;
}

const QVector3D*    Ray::origin() const
{
    return m_origin;
}

const QVector3D*    Ray::realDirection() const
{
    return m_realDirection;
}

QVector3D*    Ray::direction()
{
    return m_direction;
}

Ray*                Ray::getRay( Scene* scene, qreal x, qreal y )
{
    Ray* ray = new Ray();
    ray->setOrigin( new QVector3D( *( scene->camera() ) ) );
    ray->setRealDirection( new QVector3D( QVector3D( scene->depth(),
                                      scene->XResolution() / 2 - x ,
                                      scene->YResolution() / 2 - y ) * *scene->rotationMatrix() ) );
    ray->setDirection( new QVector3D( *ray->realDirection() ) );
    ray->m_direction->normalize();
    ray->m_realDirection->normalize();
    return ray;
}
