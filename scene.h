/*****************************************************************************
 * scene.h: Scene Class
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


#ifndef SCENE_H
#define SCENE_H

#include <QList>
#include <QVector3D>
#include <QImage>

#include "primitive.h"
#include "light.h"

class Scene
{
public:
    Scene();
    ~Scene();

    const QVector3D*    camera() const { return m_camera; }
    const QMatrix4x4*   rotationMatrix() { return m_rotationCamera; }
    qreal               depth() const { return m_depth; }
    int                 XResolution() const { return m_Xresolution; }
    int                 YResolution() const { return m_Yresolution; }
    void                setCamera( qreal, qreal, qreal );
    void                setResolution( int x, int y );
    QImage*             render();
    void                renderPixel(QImage* image, qreal x, qreal y);
    void                addPrimitive( Primitive* );
    void                addLight( Light* );
    void                getFirstIntersect( Ray& ray, IntersectionInfo& info );
    void                renderLight( Ray& ray, IntersectionInfo& info );
private:
    QList<Primitive*>&  m_primitives;
    QList<Light*>*      m_lights;
    QVector3D*          m_camera;
    QMatrix4x4*         m_rotationCamera;
    int                 m_Xresolution, m_Yresolution;
    qreal               m_depth;
};

#endif // SCENE_H
