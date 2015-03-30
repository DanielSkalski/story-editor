#include "StoryGraphWidget.h"

#include "UI/GraphicsItems/SituationNode.h"
#include "UI/GraphicsItems/ChoiceEdge.h"
#include "Model/StoryManager.h"
#include "Model/Situation.h"
#include "Model/Choice.h"


StoryGraphWidget::StoryGraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    m_StoryManager = new StoryManager();

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setSceneRect(-200, -200, 400, 400);

    setScene(scene);
    setCacheMode(CacheBackground);
    setTransformationAnchor(AnchorUnderMouse);
    setRenderHint(QPainter::Antialiasing);
    setMinimumSize(400, 400);
    setWindowTitle(tr("Story Editor"));

    createNodesAndEdges(scene);
}

void StoryGraphWidget::createNodesAndEdges(QGraphicsScene *scene)
{
    for (auto situation : m_StoryManager->situations())
    {
        SituationNode* node = new SituationNode(situation, this);
        node->setPos(situation->position);

        scene->addItem(node);

        m_SituationNodes.insert(situation->id(), node);
    }

    for (auto choice : m_StoryManager->choices())
    {
        SituationNode* sourceNode = m_SituationNodes.value(choice->from()->id());
        SituationNode* destNode = m_SituationNodes.value(choice->to()->id());

        if (sourceNode != nullptr && destNode != nullptr)
        {
            ChoiceEdge* edge = new ChoiceEdge(choice, sourceNode, destNode);

            scene->addItem(edge);

            m_ChoiceEdges.insert(choice->id(), edge);
        }
    }
}

StoryGraphWidget::~StoryGraphWidget()
{

}

void StoryGraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);
}

void StoryGraphWidget::markSituationAsSelected(Situation *situation)
{
    if (m_CurrentlySelectedNode != nullptr)
    {
        m_CurrentlySelectedNode->unmarkAsSelected();
        m_CurrentlySelectedNode->update();
    }

    m_CurrentlySelectedNode = m_SituationNodes.value(situation->id());
    m_CurrentlySelectedNode->markAsSelected();
    m_CurrentlySelectedNode->update();
}

void StoryGraphWidget::situationNodeClicked(SituationNode *situationNode)
{
    markSituationAsSelected(situationNode->situation());

    emit situationSelectionChanged(situationNode->situation());
}

void StoryGraphWidget::choiceEdgeClicked(ChoiceEdge *choiceEdge)
{

}
