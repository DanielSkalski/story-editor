#include "StoryGraphItemBase.h"
#include <QGraphicsSceneMouseEvent>

StoryGraphItemBase::StoryGraphItemBase(QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
}

StoryGraphItemBase::~StoryGraphItemBase()
{
}

void StoryGraphItemBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit mouseLeftButtonClicked();
    }

    QGraphicsObject::mousePressEvent(event);
}
