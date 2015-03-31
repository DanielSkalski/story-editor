#ifndef SITUATIONNODE_H
#define SITUATIONNODE_H

#include "Selectable.h"
#include "StoryGraphItemBase.h"

class Situation;
class ChoiceEdge;
class StoryGraphWidget;

class SituationNode : public StoryGraphItemBase, public Selectable
{
    Q_OBJECT

    Situation *m_Situation;
    StoryGraphWidget *m_StoryGraphWidget;

    int m_Width;
    int m_Height;

    QList<ChoiceEdge *> m_ChoiceEdges;

public:
    SituationNode(Situation *situation, StoryGraphWidget *storyGraphWidget, QGraphicsItem *parent = 0);

    void addChoiceEdge(ChoiceEdge *edge);
    int width() const;
    int height() const;
    Situation *situation() const;

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

};

#endif // SITUATIONNODE_H
