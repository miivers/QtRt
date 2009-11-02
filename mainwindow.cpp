/*****************************************************************************
 * mainwindow.cpp: QtRt Main Window
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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "scene.h"
#include "sphere.h"
#include "plan.h"

#include <QImage>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtRt)
{
    ui->setupUi(this);
    connect(ui->actionRender, SIGNAL(triggered()), this, SLOT(renderScene()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void    MainWindow::renderScene()
{
    QImage* image;
    Scene* scene = new Scene();
    scene->setCamera( -3000, 0, 300 );
    scene->addPrimitive( new Sphere(0, 0, 0, 200) );
    scene->addPrimitive( new Plan( 0, 0, 0 ) );
    scene->addLight( new Light(-100, -50, 100, Qt::yellow ) );
    image = scene->render();
    ui->label->setPixmap( QPixmap::fromImage( *image ) );
}
