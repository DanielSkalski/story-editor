#include "ChoiceEdge.h"

#include "Model/Choice.h"
#include "UI/GraphicsItems/SituationNode.h"
#include "UI/Widgets/StoryGraphWidget.h"

#include <QPainter>
#include <math.h>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

ChoiceEdge::ChoiceEdge(Choice *choice, SituationNode *sourceNode, SituationNode* destNode)
    : m_Choice(choice), m_SourceNode(sourceNode), m_DestNode(destNode)
{
    m_SourceNode->addChoiceEdge(this);
    m_DestNode->addChoiceEdge(this);
    adjust();
}

void ChoiceEdge::adjust()
{
    if (m_SourceNode == nullptr || m_DestNode == nullptr)
        return;

    QLineF line(mapFromItem(m_SourceNode, 0, 0), mapFromItem(m_DestNode, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.))
    {
        QPointF sourceEdgeOffset;
        QPointF destEdgeOffset;

        determineEdgeEndPointsOffsets(sourceEdgeOffset, destEdgeOffset, line);

        m_SourcePoint = line.p1() + sourceEdgeOffset;
        m_DestPoint = line.p2() + destEdgeOffset;
    }
    else
    {
        m_SourcePoint = m_DestPoint = line.p1();
    }
}

void ChoiceEdge::determineEdgeEndPointsOffsets(QPointF& sourceOffset, QPointF& destOffset, const QLineF& line)
{
    if (abs(line.dy()) > abs(line.dx()))
    {
        if (line.dy() > 0)
        {
            sourceOffset = getBottomPoint(m_SourceNode);
            destOffset = getTopPoint(m_DestNode);
        }
        else
        {
            sourceOffset = getTopPoint(m_SourceNode);
            destOffset = getBottomPoint(m_DestNode);
        }
    }
    else
    {
        if (line.dx() > 0)
        {
            sourceOffset = getRightPoint(m_SourceNode);
            destOffset = getLeftPoint(m_DestNode);
        }
        else
        {
            sourceOffset = getLeftPoint(m_SourceNode);
            destOffset = getRightPoint(m_DestNode);
        }
    }
}

QRectF ChoiceEdge::boundingRect() const
{
    if (m_SourceNode == nullptr || m_DestNode == nullptr)
        return QRectF();

    qreal penWidth = 1;
    qreal arrowSize = 10;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(m_SourcePoint, QSizeF(m_DestPoint.x() - m_SourcePoint.x(),
                                      m_DestPoint.y() - m_SourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void ChoiceEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (m_SourceNode == nullptr || m_DestNode == nullptr)
        return;

    QLineF line(m_SourcePoint, m_DestPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    QPolygonF arrow = createArrow(line);

    painter->setBrush(Qt::black);
    painter->drawPolygon(arrow);
}

QPolygonF ChoiceEdge::createArrow(const QLineF& line) const
{
    qreal arrowSize = 10;

    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
    {
        angle = TwoPi - angle;
    }

    QPointF destArrowP1 = m_DestPoint + QPointF(sin(angle - Pi / 3) * arrowSize,
                                              cos(angle - Pi / 3) * arrowSize);
    QPointF destArrowP2 = m_DestPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
                                              cos(angle - Pi + Pi / 3) * arrowSize);

    return QPolygonF() << line.p2() << destArrowP1 << destArrowP2;
}
