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

#ifndef QtVertexItem_H
#define QtVertexItem_H

#include "graphconcept.h"

#include <QGraphicsItem>
#include <QList>

class QtEdgeItem;
class GraphWidget;

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

enum VertexState{normal_state, important_state,selected_state, active_state,unimportant_state, lfp_state, startnode_state, vertexOfInterest_state};
enum VertexType{normal_type, LFP_type, span_type};
enum VertexTag{no_tag, disabled_tag, selected_tag};

class QtVertexItem : public QGraphicsItem
{
public:
    QtVertexItem(GraphWidget *graphWidget, QPointF& pos, QString name="");

    void addEdge(QtEdgeItem *edge);
    QList<QtEdgeItem *> edges() const;

    enum { Type = UserType + 1 };
    int type() const { return Type; }

    void calculateForces();
    bool advance();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QString strLabel;
    QGraphicsTextItem* itemLabel;

    vertex_descriptor getVertexDescriptor(){return mV;}

    void setState(VertexState state);
    void setTag(VertexTag tag){mTag=tag;}
    VertexTag getTag(){return mTag;}
    VertexState mState;
    VertexType mType;
    VertexTag mTag;


    void setType(VertexType type);
    VertexType getType(){return mType;}

    void copyTo(GraphWidget* gWidget);

    vertex_descriptor getClone(){return mClone;}
    void setClone(vertex_descriptor clone){mClone=clone;}

    bool isCopied(){return mCopied;}

    int mSaveIndex;

    void unsetClone (){mCopied=false; mClone=0;}

    std::vector<QtVertexItem*> surroundingNodes;
    int degree;
protected:
    bool mCopied;

    vertex_descriptor mClone;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    
    vertex_descriptor mV;
    Graph* mG;
private:
    QList<QtEdgeItem *> edgeList;
    QPointF newPos;
    GraphWidget *graph;
};

#endif
