#ifndef CHOICEEDGE_H
#define CHOICEEDGE_H


#include <QGraphicsItem>
#include "SituationNode.h"
#include "Selectable.h"
#include "StoryGraphItemBase.h"

class Choice;
class StoryGraphWidget;

class ChoiceEdge : public StoryGraphItemBase, public Selectable
{
    Q_OBJECT

    Choice *m_Choice;

    SituationNode *m_SourceNode;
    SituationNode *m_DestNode;

    QPointF m_SourcePoint;
    QPointF m_DestPoint;

public:
    ChoiceEdge(Choice *choice, SituationNode *sourceNode, SituationNode *destNode, QGraphicsItem *parent = 0);

    void adjust();
    Choice *choice() const;

protected:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

private:
    void determineEdgeEndPointsOffsets(QPointF& sourceOffset, QPointF& destOffset, const QLineF& line);
    QPolygonF createArrow(const QLineF& line) const;

    inline QPointF getBottomPoint(SituationNode *node) const
    {
        return QPointF(node->width() / 2, node->height());
    }

    inline QPointF getTopPoint(SituationNode *node) const
    {
        return QPointF(node->width() / 2, 0);
    }

    inline QPointF getLeftPoint(SituationNode *node) const
    {
        return QPointF(0, node->height() / 2);
    }

    inline QPointF getRightPoint(SituationNode *node) const
    {
        return QPointF(node->width(), node->height() / 2);
    }
};

#endif // CHOICEEDGE_H
