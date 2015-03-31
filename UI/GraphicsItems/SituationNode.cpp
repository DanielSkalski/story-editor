#include "SituationNode.h"

#include <QPainter>

#include "Model/Situation.h"
#include "UI/GraphicsItems/ChoiceEdge.h"
#include "UI/Widgets/StoryGraphWidget.h"


SituationNode::SituationNode(Situation *situation, StoryGraphWidget *storyGraphWidget, QGraphicsItem *parent)
    : StoryGraphItemBase(parent), Selectable(), m_Situation(situation), m_StoryGraphWidget(storyGraphWidget)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setZValue(-1);

    m_Width = 80;
    m_Height = 60;
}

void SituationNode::addChoiceEdge(ChoiceEdge *edge)
{
    m_ChoiceEdges << edge;
    edge->adjust();
}

int SituationNode::width() const
{
    return m_Width;
}

int SituationNode::height() const
{
    return m_Height;
}

Situation *SituationNode::situation() const
{
    return m_Situation;
}

QRectF SituationNode::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(0 - adjust, 0 - adjust, m_Width + adjust, m_Height + adjust);
}

void SituationNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (m_IsSelected)
    {
        painter->setPen(Qt::blue);
    }
    else
    {
        painter->setPen(Qt::black);
    }

    painter->setBrush(Qt::white);
    painter->drawRect(0, 0, m_Width, m_Height);
    painter->drawText(QRectF(6, 6, m_Width - 6, 20), m_Situation->id());
}

QVariant SituationNode::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged)
    {
        for (auto edge : m_ChoiceEdges)
        {
            edge->adjust();
        }
    }

    return QGraphicsItem::itemChange(change, value);
}
