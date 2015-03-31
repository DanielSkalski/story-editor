#ifndef STORYGRAPHITEMBASE_H
#define STORYGRAPHITEMBASE_H

#include <QGraphicsObject>

class StoryGraphItemBase : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit StoryGraphItemBase(QGraphicsItem *parent = 0);
    virtual ~StoryGraphItemBase();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

signals:
    void mouseLeftButtonClicked();
};

#endif // STORYGRAPHITEMBASE_H
