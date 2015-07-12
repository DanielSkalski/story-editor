#include "StoryGraphWidget.h"

#include "UI/GraphicsItems/SituationNode.h"
#include "UI/GraphicsItems/ChoiceEdge.h"
#include "Model/StoryManager.h"
#include "Model/Situation.h"
#include "Model/Choice.h"

#include <QMenu>
#include <QContextMenuEvent>

StoryGraphWidget::StoryGraphWidget(StoryManager *storyManager, QWidget *parent)
    : QGraphicsView(parent), m_StoryManager(storyManager), m_CurrentlySelectedItem(nullptr)
{
    m_Scene = new QGraphicsScene(this);
//    m_Scene->setSceneRect(-200, -200, 400, 400);

    setScene(m_Scene);
    setCacheMode(CacheBackground);
    setTransformationAnchor(AnchorUnderMouse);
    setRenderHint(QPainter::Antialiasing);
    setMinimumSize(400, 400);
    setWindowTitle(tr("Story Editor"));

    createNodesAndEdges();

    connect(m_StoryManager, SIGNAL(addedSituation(Situation*)),
            this, SLOT(addSituation(Situation*)));

    connect(m_StoryManager, SIGNAL(addedChoice(Choice*)),
            this, SLOT(addChoice(Choice*)));

    connect(m_StoryManager, SIGNAL(loadedStory()),
            this, SLOT(onLoadedStory()));
}

void StoryGraphWidget::createNodesAndEdges()
{
    for (auto situation : m_StoryManager->situations())
    {
        createSituationNode(situation);
    }

    for (auto choice : m_StoryManager->choices())
    {
        createChoiceEdge(choice);
    }
}

void StoryGraphWidget::deleteNodesAndEdges()
{
    for (auto edge : m_ChoiceEdges)
    {
        disconnect(edge->choice());
        disconnect(edge);
        delete edge;
    }
    m_ChoiceEdges.clear();

    for (auto node : m_SituationNodes)
    {
        disconnect(node->situation());
        disconnect(node);
        delete node;
    }
    m_SituationNodes.clear();

    m_Scene->clear();
}

StoryGraphWidget::~StoryGraphWidget()
{
    deleteNodesAndEdges();
}

void StoryGraphWidget::contextMenuEvent(QContextMenuEvent *event)
{
    if (this->itemAt(event->pos()) == nullptr)
    {
        QMenu *menu = new QMenu;
        QAction *addSituationAction = new QAction(tr("New situation"), menu);

        menu->addAction(addSituationAction);

        connect(addSituationAction, &QAction::triggered, [=]
        {
//            auto ePos = event->pos();
//            auto glPos = event->globalPos();
//            auto pos = this->mapFromGlobal(glPos);
//            auto scenePos = this->mapToScene(QRect(pos, QSize(2,2)));
//            addEmptySituationAt(scenePos.boundingRect().center());
        });

        menu->popup(event->globalPos());
    }

    QGraphicsView::contextMenuEvent(event);
}

void StoryGraphWidget::markSituationAsSelected(Situation *situation)
{
    Selectable* node = (Selectable *)m_SituationNodes.value(situation->id());
    markAsSelected(node);

    emit situationSelectionChanged(situation);
}

void StoryGraphWidget::markChoiceAsSelected(Choice *choice)
{
    Selectable* edge = (Selectable *)m_ChoiceEdges.value(choice->id());
    markAsSelected(edge);

    emit choiceSelectionChanged(choice);
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

void StoryGraphWidget::createSituationNode(Situation *situation)
{
    SituationNode *node = new SituationNode(situation, this);
    node->setPos(situation->position);

    connect(situation, SIGNAL(idHasChanged(QString,QString)), this, SLOT(onSituationIdHasChanged(QString,QString)));
    connect(node, &SituationNode::mouseLeftButtonClicked, [=]
    {
        onSituationNodeClicked(node);
    });

    m_Scene->addItem(node);

    m_SituationNodes.insert(situation->id(), node);
}

void StoryGraphWidget::createChoiceEdge(Choice *choice)
{
    SituationNode *sourceNode = m_SituationNodes.value(choice->from()->id());
    SituationNode *destNode = m_SituationNodes.value(choice->to()->id());

    if (sourceNode != nullptr && destNode != nullptr)
    {
        ChoiceEdge *edge = new ChoiceEdge(choice, sourceNode, destNode);

        connect(choice, SIGNAL(idHasChanged(QString,QString)), this, SLOT(onChoiceIdHasChanged(QString,QString)));
        connect(edge, &ChoiceEdge::mouseLeftButtonClicked, [=]
        {
           onChoiceEdgeClicked(edge);
        });

        m_Scene->addItem(edge);

        m_ChoiceEdges.insert(choice->id(), edge);
    }
}

void StoryGraphWidget::addSituation(Situation *situation)
{
    createSituationNode(situation);
    markSituationAsSelected(situation);
}

void StoryGraphWidget::addChoice(Choice *choice)
{
    createChoiceEdge(choice);
    markChoiceAsSelected(choice);
}

void StoryGraphWidget::onSituationIdHasChanged(const QString &oldId, const QString &newId)
{
    auto situationNode = m_SituationNodes.take(oldId);
    m_SituationNodes.insert(newId, situationNode);
}

void StoryGraphWidget::onChoiceIdHasChanged(const QString &oldId, const QString &newId)
{
    auto choiceEdge = m_ChoiceEdges.take(oldId);
    m_ChoiceEdges.insert(newId, choiceEdge);
}

void StoryGraphWidget::onSituationNodeClicked(SituationNode *situationNode)
{
    auto situation = situationNode->situation();
    markSituationAsSelected(situation);
}

void StoryGraphWidget::onChoiceEdgeClicked(ChoiceEdge *choiceEdge)
{
    auto choice = choiceEdge->choice();
    markChoiceAsSelected(choice);
}

void StoryGraphWidget::onLoadedStory()
{
    m_CurrentlySelectedItem = nullptr;

    deleteNodesAndEdges();
    createNodesAndEdges();
}
