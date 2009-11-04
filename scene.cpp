/*****************************************************************************
 * scene.cpp: Scene class
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

#include <QColor>
#include <QMatrix4x4>
#include <QtDebug>
#include <float.h>
#include <math.h>

#include "scene.h"

Scene::Scene() : m_primitives( *new QList<Primitive*>() )
{
    m_camera = new QVector3D(0, 0, 0);
    m_rotationCamera = new QMatrix4x4();
    m_rotationCamera->setIdentity();
    m_rotationCamera->rotate(0.0, 1.0, 0.0, 0.0);
    m_rotationCamera->rotate(-5.0, 0.0, 1.0, 0.0);
    m_rotationCamera->rotate(0.0, 0.0, 0.0, 1.0);
    m_rotationCamera->inferSpecialType();
    m_depth = 1000;
    m_Xresolution = 800;
    m_Yresolution = 600;
    m_lights = new QList<Light*>();
}

Scene::~Scene()
{
    delete m_camera;
    delete m_lights;
    delete &m_primitives;
}

void    Scene::setCamera( qreal x, qreal y, qreal z )
{
    if ( m_camera )
        delete m_camera;
    m_camera = new QVector3D(x, y, z);
}

void    Scene::setResolution( int x, int y )
{
    m_Xresolution = x;
    m_Yresolution = y;
}

void    Scene::addPrimitive( Primitive* primitive )
{
    m_primitives.append( primitive );
}

void    Scene::addLight( Light* light )
{
    m_lights->append( light );
}

QImage* Scene::render()
{
    QImage*     image = new QImage( m_Xresolution,
                                    m_Yresolution,
                                    QImage::Format_RGB888 );

    for ( qreal y = 0; y < m_Yresolution; ++y )
    {
        for ( qreal x = 0; x < m_Xresolution; ++x )
        {
            renderPixel( image, x, y );
        }
    }
    return image;
}

void    Scene::renderPixel( QImage* image, qreal x, qreal y )
{
    IntersectionInfo info;
    Ray* ray = Ray::getRay( this, x, y );
    image->setPixel(x, y, Qt::black);
    getFirstIntersect( *ray, info );
    if ( info.hit )
    {
        image->setPixel( x, y, info.primitive->color().rgb() );
    }
    delete ray;
}

void    Scene::getFirstIntersect( Ray& ray, IntersectionInfo& info )
{
    IntersectionInfo result;

    int index = 0;
    int counter = m_primitives.count();
    info.hit = false;
    info.distance = DBL_MAX;
    info.primitive = NULL;
    while ( index < counter )
    {
        ray.setDirection( new QVector3D( ray.direction() *
                                          m_primitives[index]->rotationMatrix() ) );
        m_primitives[index]->intersect( ray, result );
        if ( result.hit && result.distance < info.distance && result.distance > 0.0 )
        {
            info.hit = true;
            info.distance = result.distance;
            info.primitive = m_primitives[index];
        }
        ++index;
    }
}

void    Scene::renderLight( Ray& ray, IntersectionInfo& info )
{
    info.position = new QVector3D( ray.origin() + ray.direction() * info.distance );
    //info.normal =
}
