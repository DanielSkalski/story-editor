#include "StoryGraphWidget.h"

#include "UI/GraphicsItems/SituationNode.h"
#include "UI/GraphicsItems/ChoiceEdge.h"
#include "Model/StoryManager.h"
#include "Model/Situation.h"
#include "Model/Choice.h"


StoryGraphWidget::StoryGraphWidget(QWidget *parent)
    : QGraphicsView(parent), m_CurrentlySelectedItem(nullptr)
{
    m_StoryManager = new StoryManager();

    m_Scene = new QGraphicsScene(this);
    m_Scene->setSceneRect(-200, -200, 400, 400);

    setScene(m_Scene);
    setCacheMode(CacheBackground);
    setTransformationAnchor(AnchorUnderMouse);
    setRenderHint(QPainter::Antialiasing);
    setMinimumSize(400, 400);
    setWindowTitle(tr("Story Editor"));

    createNodesAndEdges();
}

void StoryGraphWidget::createNodesAndEdges()
{
    for (auto situation : m_StoryManager->situations())
    {
        addSituation(situation);
    }

    for (auto choice : m_StoryManager->choices())
    {
        addChoice(choice);
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
    Selectable* node = (Selectable *)m_SituationNodes.value(situation->id());
    markAsSelected(node);
}

void StoryGraphWidget::markChoiceAsSelected(Choice *choice)
{
    Selectable* edge = (Selectable *)m_ChoiceEdges.value(choice->id());
    markAsSelected(edge);
}

void StoryGraphWidget::markAsSelected(Selectable *item)
{
    if (m_CurrentlySelectedItem != nullptr)
    {
        m_CurrentlySelectedItem->unmarkAsSelected();
        dynamic_cast<QGraphicsObject *>(m_CurrentlySelectedItem)->update();
    }

    m_CurrentlySelectedItem = item;

    if (m_CurrentlySelectedItem != nullptr)
    {
        m_CurrentlySelectedItem->markAsSelected();
        dynamic_cast<QGraphicsObject *>(m_CurrentlySelectedItem)->update();
    }
}

void StoryGraphWidget::addSituation(Situation *situation)
{
    SituationNode *node = new SituationNode(situation, this);
    node->setPos(situation->position);

    connect(situation, SIGNAL(idHasChanged(QString,QString)), this, SLOT(situationIdHasChanged(QString,QString)));
    connect(node, &SituationNode::mouseLeftButtonClicked, [=]
    {
        situationNodeClicked(node);
    });

    m_Scene->addItem(node);

    m_SituationNodes.insert(situation->id(), node);
}

void StoryGraphWidget::addChoice(Choice *choice)
{
    SituationNode *sourceNode = m_SituationNodes.value(choice->from()->id());
    SituationNode *destNode = m_SituationNodes.value(choice->to()->id());

    if (sourceNode != nullptr && destNode != nullptr)
    {
        ChoiceEdge *edge = new ChoiceEdge(choice, sourceNode, destNode);

        connect(choice, SIGNAL(idHasChanged(QString,QString)), this, SLOT(choiceIdHasChanged(QString,QString)));
        connect(edge, &ChoiceEdge::mouseLeftButtonClicked, [=]
        {
           choiceEdgeClicked(edge);
        });

        m_Scene->addItem(edge);

        m_ChoiceEdges.insert(choice->id(), edge);
    }
}

void StoryGraphWidget::situationIdHasChanged(const QString &oldId, const QString &newId)
{
    auto situationNode = m_SituationNodes.take(oldId);
    m_SituationNodes.insert(newId, situationNode);
}

void StoryGraphWidget::choiceIdHasChanged(const QString &oldId, const QString &newId)
{
    auto choiceEdge = m_ChoiceEdges.take(oldId);
    m_ChoiceEdges.insert(newId, choiceEdge);
}

void StoryGraphWidget::situationNodeClicked(SituationNode *situationNode)
{
    auto situation = situationNode->situation();
    markSituationAsSelected(situation);

    emit situationSelectionChanged(situation);
}

void StoryGraphWidget::choiceEdgeClicked(ChoiceEdge *choiceEdge)
{
    auto choice = choiceEdge->choice();
    markChoiceAsSelected(choice);

    emit choiceSelectionChanged(choice);
}
