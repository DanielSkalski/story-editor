#ifndef STORYGRAPHWIDGET_H
#define STORYGRAPHWIDGET_H

#include <QGraphicsView>
#include <QHash>
#include <QString>

class StoryManager;
class SituationNode;
class ChoiceEdge;
class Situation;

class StoryGraphWidget : public QGraphicsView
{
    Q_OBJECT

    StoryManager *m_StoryManager;
    QHash<QString, SituationNode *> m_SituationNodes;
    QHash<QString, ChoiceEdge *> m_ChoiceEdges;

    SituationNode *m_CurrentlySelectedNode;

public:
    explicit StoryGraphWidget(QWidget *parent = 0);
    ~StoryGraphWidget();

private:
    void createNodesAndEdges(QGraphicsScene *scene);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;

signals:
    void situationSelectionChanged(Situation *situation);

public slots:
    void markSituationAsSelected(Situation *situation);
    void situationNodeClicked(SituationNode *situationNode);
    void choiceEdgeClicked(ChoiceEdge *choiceEdge);
};

#endif // STORYGRAPHWIDGET_H
