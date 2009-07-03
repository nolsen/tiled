/*
 * Tiled Map Editor (Qt)
 * Copyright 2008-2009 Tiled (Qt) developers (see AUTHORS file)
 *
 * This file is part of Tiled (Qt).
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef MAPOBJECTITEM_H
#define MAPOBJECTITEM_H

#include <QGraphicsItem>

namespace Tiled {

class MapObject;

namespace Internal {

class MapDocument;
class ObjectGroupItem;
class ResizeHandle;

/**
 * A graphics item displaying a map object.
 */
class MapObjectItem : public QGraphicsItem
{
public:
    /**
     * Constructor.
     *
     * @param object the object to be displayed
     * @param parent the item of the object group this object belongs to
     */
    MapObjectItem(MapObject *object, ObjectGroupItem *parent);

    MapObject *mapObject() const
    { return mObject; }

    /**
     * Should be called when the map object this item refers to was changed.
     */
    void syncWithMapObject();

    bool isEditable() const
    { return mIsEditable; }

    /**
     * Sets whether this map object is editable. Editable map objects can be
     * moved and resized, and their properties can be edited.
     */
    void setEditable(bool editable);

    // QGraphicsItem
    QRectF boundingRect() const;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    void setSize(int width, int height);
    MapDocument *mapDocument() const;
    Qt::GlobalColor colorForType() const;

    MapObject *mObject;
    ResizeHandle *mResizeHandle;
    QPoint mOldPos;
    QSize mSize;    // Copy of size for adapting to geometry change correctly
    bool mIsEditable;

    friend class ResizeHandle;
};

} // namespace Internal
} // namespace Tiled

#endif // MAPOBJECTITEM_H