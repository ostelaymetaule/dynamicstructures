/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the example classes of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QtGui/QGraphicsView>
#include <QGraphicsTextItem>
#include "graphconcept.h"

//class QtVertexItem;
//class QtEdgeItem;

#include "QtVertexItem.h"
#include "QtEdgeItem.h"

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget* parent);

    void itemMoved();

  QtVertexItem* getClosestNodeTo(QtVertexItem* node);

  QtVertexItem* addNode(QPointF& pos,QString& name);
  QtEdgeItem* addEdge(vertex_descriptor& u, vertex_descriptor& v, int directed);


  Graph* mGraph; //boost adjacency list<vecS, vecS, undirectedS, gVertex, gEdge>
  void setGraphStructure(Graph* graph){mGraph = graph;}

   QGraphicsScene* scene;

    Graph* getGraph(){return mGraph;}
    void setArea(QRect& area){mArea= area;}

protected:
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    void wheelEvent(QWheelEvent *event);
    //void mousePressEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent *event);

    void drawBackground(QPainter *painter, const QRectF &rect);

    void scaleView(qreal scaleFactor);



    QRect mArea;

private:
    int timerId;
    QList<QtVertexItem*> nodes;
    QList<QtEdgeItem*> edges;

    QtVertexItem *centerNode;
};

#endif
