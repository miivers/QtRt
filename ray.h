/*****************************************************************************
 * ray.h: Ray class
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


#ifndef RAY_H
#define RAY_H

#include <QVector3D>

class Scene;

class Ray
{
public:
    Ray();
    Ray( QVector3D*, QVector3D* );
    ~Ray();

    void                setOrigin( QVector3D* );
    void                setDirection( QVector3D* );
    const QVector3D&    origin() const;
    const QVector3D&    direction() const;
    static Ray*         getRay( Scene* scene, qreal x, qreal y );
private:
    QVector3D*          m_origin;
    QVector3D*          m_realDirection;
    QVector3D*          m_direction;
};

#endif // RAY_H
