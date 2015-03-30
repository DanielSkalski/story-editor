#ifndef SITUATIONNODE_H
#define SITUATIONNODE_H

#include <QGraphicsItem>

class Situation;
class ChoiceEdge;
class StoryGraphWidget;

class SituationNode : public QGraphicsItem
{
    Situation* m_Situation;
    StoryGraphWidget* m_StoryGraphWidget;

    int m_Width;
    int m_Height;

    QList<ChoiceEdge*> m_ChoiceEdges;

public:
    SituationNode(Situation* situation, StoryGraphWidget* storyGraphWidget);

    void addChoiceEdge(ChoiceEdge* edge);
    int width() const;
    int height() const;

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
};

#endif // SITUATIONNODE_H
