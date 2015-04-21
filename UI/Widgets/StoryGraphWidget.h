#ifndef STORYGRAPHWIDGET_H
#define STORYGRAPHWIDGET_H

#include <QGraphicsView>
#include <QHash>
#include <QString>
#include "UI/GraphicsItems/Selectable.h"

class StoryManager;
class SituationNode;
class ChoiceEdge;
class Situation;
class Choice;
class QPoint;

class StoryGraphWidget : public QGraphicsView
{
    Q_OBJECT

    StoryManager *m_StoryManager;
    QGraphicsScene *m_Scene;

    QHash<QString, SituationNode *> m_SituationNodes;
    QHash<QString, ChoiceEdge *> m_ChoiceEdges;

    Selectable *m_CurrentlySelectedItem;

public:
    explicit StoryGraphWidget(StoryManager *storyManager,  QWidget *parent = 0);
    ~StoryGraphWidget();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

private:
    void createNodesAndEdges();
    void markAsSelected(Selectable *item);
    void createSituationNode(Situation *situation);
    void createChoiceEdge(Choice *choice);

signals:
    void situationSelectionChanged(Situation *situation);
    void choiceSelectionChanged(Choice *choice);

public slots:
    void markSituationAsSelected(Situation *situation);
    void markChoiceAsSelected(Choice *choice);

    void addSituation(Situation *situation);
    void addChoice(Choice *choice);

private slots:
    void onSituationIdHasChanged(const QString& oldId, const QString& newId);
    void onChoiceIdHasChanged(const QString& oldId, const QString& newId);

    void onSituationNodeClicked(SituationNode *situationNode);
    void onChoiceEdgeClicked(ChoiceEdge *choiceEdge);
};

#endif // STORYGRAPHWIDGET_H
