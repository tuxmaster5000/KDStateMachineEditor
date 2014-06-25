/*
  quickprimitiveitem.h

  This file is part of the KDAB State Machine Editor Library.

  Copyright (C) 2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com.
  All rights reserved.
  Author: Kevin Funk <kevin.funk@kdab.com>

  Licensees holding valid commercial KDAB State Machine Editor Library
  licenses may use this file in accordance with the KDAB State Machine Editor
  Library License Agreement provided with the Software.

  This file may be distributed and/or modified under the terms of the
  GNU Lesser General Public License version 2.1 as published by the
  Free Software Foundation and appearing in the file LICENSE.LGPL.txt included.

  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

  Contact info@kdab.com if any conditions of this licensing are not
  clear to you.
*/

#ifndef KDSME_QUICK_QUICKPRIMITIVEITEM_H
#define KDSME_QUICK_QUICKPRIMITIVEITEM_H

#include <QScopedPointer>
#include <QtQuick/QSGGeometry>
#include <QtQuick/QQuickItem>

class QRectF;

namespace GeometryUtils {

QRectF boundingRect(QSGGeometry* geometry);

}

class QuickGeometryItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<qreal> data READ vertexData WRITE setVertexData NOTIFY vertexDataChanged)
    Q_PROPERTY(QuickGeometryItem::VertexDataType type READ dataType READ vertexDataType WRITE setVertexDataType NOTIFY vertexDataTypeChanged)
    Q_PROPERTY(float lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)

    Q_PROPERTY(unsigned int drawingMode READ drawingMode READ drawingMode WRITE setDrawingMode NOTIFY drawingModeChanged)
    Q_ENUMS(VertexDataType);
    Q_ENUMS(DrawingMode);

public:
    enum VertexDataType {
        Point2DType, ///< Default
        ColoredPoint2DType,
        TexturedPoint2DType
    };
    enum DrawingMode {
        Points = GL_POINTS,
        Lines = GL_LINES,
        LineLoop = GL_LINE_LOOP,
        LineStrip = GL_LINE_STRIP,
        Triangles = GL_TRIANGLES,
        TriangleStrip = GL_TRIANGLE_STRIP,
        TriangleFan = GL_TRIANGLE_FAN,
        // According to Sean, these are unsupported on modern OpenGL and ES2
        /*
        Quads = GL_QUADS,
        QuadStrip = GL_QUAD_STRIP,
        Polygon = GL_POLYGON
        */
    };

    explicit QuickGeometryItem(QObject* parent = 0);

    QList<qreal> vertexData() const;
    void setVertexData(const QList<qreal>& vertexData);

    VertexDataType vertexDataType() const;
    void setVertexDataType(VertexDataType type);

    GLenum drawingMode() const;
    void setDrawingMode(GLenum drawingMode);

    float lineWidth() const;
    void setLineWidth(float lineWidth);

    QSGGeometry* createGeometry() const;

Q_SIGNALS:
    void vertexDataChanged(const QList<qreal>& vertexData);
    void vertexDataTypeChanged(VertexDataType type);
    void drawingModeChanged(GLenum drawingMode);
    void lineWidthChanged(float lineWidth);
    /// Emitted in case any of this object properties changes
    void changed();

private:
    QList<qreal> m_vertexData;
    VertexDataType m_vertexDataType;
    GLenum m_drawingMode;
    float m_lineWidth;
};

Q_DECLARE_METATYPE(QuickGeometryItem::VertexDataType);
Q_DECLARE_METATYPE(QuickGeometryItem::DrawingMode);

class QuickPrimitiveItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QuickGeometryItem* geometry READ geometryItem WRITE setGeometryItem NOTIFY geometryItemChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    explicit QuickPrimitiveItem(QQuickItem* parent = 0);

    QuickGeometryItem* geometryItem() const;
    void setGeometryItem(QuickGeometryItem* item);

    QColor color() const;
    void setColor(const QColor& color);

Q_SIGNALS:
    void geometryItemChanged(QuickGeometryItem* geometry);
    void colorChanged(const QColor& color);

protected:
    virtual QSGNode *updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData* data) Q_DECL_OVERRIDE;

private Q_SLOTS:
    void updateGeometry();

private:
    void updateImplicitSize(QSGGeometry* geometry);

    QuickGeometryItem* m_geometryItem;
    bool m_geometryDirty;
    QColor m_color;
};

#endif // QUICKPRIMITIVEITEM_H