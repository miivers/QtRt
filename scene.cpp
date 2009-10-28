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

Scene::Scene()
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
    m_primitives = new QList<Primitive*>();
    m_lights = new QList<Light*>();
}

Scene::~Scene()
{
    delete m_camera;
    delete m_primitives;
    delete m_lights;
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
    qreal distance = DBL_MAX;
    qreal result = -1;
    Primitive*  primitive = NULL;
    int index = 0;
    int counter = m_primitives->count();
    Ray* ray = Ray::getRay( this, x, y );

    image->setPixel(x, y, Qt::black);
    while ( index < counter )
    {
        ray->setDirection( new QVector3D( ( *ray->realDirection() ) *
                                          ( * ( ( *m_primitives )[index]->rotationMatrix() ) ) ) );
        result = (*m_primitives)[index]->intersect( ray );
        if ( ( result < distance ) && result > 0.0 )
        {
            distance = result;
            primitive = (*m_primitives)[index];
            image->setPixel( x, y, (*m_primitives)[index]->color().rgb() );
        }
        ++index;
    }
    if ( !primitive )
        return;
    qreal cosinus = 0.0;
    QVector3D* intersect = new QVector3D( *ray->origin() + distance * *ray->realDirection() );
    QVector3D* normal = primitive->normal( intersect );
    QVector3D* realNormal = new QVector3D( (*normal) * (primitive->rotationMatrix()->inverted()) );
    QVector3D* lightVector = NULL;
    delete normal;
    for ( index = 0, counter = m_lights->count(); index < counter; ++index )
    {
        lightVector = new QVector3D( ( * ( *m_lights )[index]->position() ) - ( *intersect ) );
        cosinus = QVector3D::dotProduct( *realNormal, *ray->direction() ) /
                  ( realNormal->length() * lightVector->length() );
        if ( QVector3D::dotProduct( *realNormal, *ray->direction() ) )
            cosinus = -cosinus;
        if ( cosinus > 1.0 )
            cosinus = 1.0;
        if ( cosinus < ZERO )
            continue;
        /*if ( QVector3D::dotProduct( *normal, *normal ) <= ZERO )
            continue;
        QVector3D* dist = new QVector3D( *(*m_lights)[index]->position() - *intersect );
        if ( sqrt( QVector3D::dotProduct( *normal, *dist ) ) <= ZERO )
            continue;
        Ray* lightRay = new Ray( new QVector3D( *intersect ),
                                 new QVector3D( 1.0 / sqrt( QVector3D::dotProduct( *dist, *dist ) ) * ( *dist )  ) );
        double lambert = QVector3D::dotProduct( *lightRay->direction(), *normal ) * 1.0;
        qDebug() << *lightRay->direction() << *normal;*/
        //qDebug() << cosinus << primitive->color();
        QColor color(QColor::Rgb);
        /*if ( dynamic_cast<Plan*>(primitive) )
            qDebug() << primitive->color().blue() << cosinus * 100;*/

        color.setRed( primitive->color().red() * cosinus * (*m_lights)[index]->color().red() );
        color.setGreen( primitive->color().green() * cosinus * (*m_lights)[index]->color().green() );
        color.setBlue( primitive->color().blue() * cosinus * (*m_lights)[index]->color().blue() );
        //qDebug() << cosinus;
        image->setPixel( x, y, color.rgb() );
    }
}
