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
#include <QtDebug>

#include <float.h>
#include "scene.h"

Scene::Scene()
{
    m_camera = new QVector3D(0, 0, 0);
    m_depth = 100;
    m_Xresolution = 480;
    m_Yresolution = 320;
    m_primitives = new QList<Primitive*>();
}

Scene::~Scene()
{
    delete m_camera;
    delete m_primitives;
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
    m_primitives->append( primitive );
}

QImage* Scene::render()
{
    QImage*     image = new QImage( m_Xresolution,
                                    m_Yresolution,
                                    QImage::Format_RGB888 );
    qreal       distance;
    qreal       result = -1;
    Ray*        ray;
    int         primitives = m_primitives->count();
    int         primitiveIndex = 0;
    QColor        color( Qt::black );
    for ( int y = 0; y < m_Yresolution; ++y )
    {
        for ( int x = 0; x < m_Xresolution; ++x )
        {
            image->setPixel(x, y, Qt::black);
            distance = DBL_MAX;
            ray = Ray::getRay( this, x, y );
            /*QVector3D direction( m_depth, m_Xresolution / 2 - x, m_Yresolution / 2 - y );
            direction.setX( direction.x() + m_camera->x() );
            direction.setY( direction.y() + m_camera->y() );
            direction.setZ( direction.z() + m_camera->z() );*/
            primitiveIndex = 0;
            while ( primitiveIndex < primitives )
            {
                result = (*m_primitives)[primitiveIndex]->intersect( ray );
                if ( ( result < distance ) && result > 0.0 )
                {
                    distance = result;
                    image->setPixel( x, y, (*m_primitives)[primitiveIndex]->getColor().rgb() );
                }
                ++primitiveIndex;
            }
            delete ray;
        }
    }
    return image;
}
