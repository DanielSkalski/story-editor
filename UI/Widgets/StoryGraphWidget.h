#ifndef STORYGRAPHWIDGET_H
#define STORYGRAPHWIDGET_H

#include <QGraphicsView>
#include <QHash>
#include <QString>

class StoryManager;
class SituationNode;
class ChoiceEdge;

class StoryGraphWidget : public QGraphicsView
{
    Q_OBJECT

    StoryManager * m_StoryManager;
    QHash<QString, SituationNode*> m_SituationNodes;
    QHash<QString, ChoiceEdge*> m_ChoiceEdges;

public:
    explicit StoryGraphWidget(QWidget *parent = 0);
    ~StoryGraphWidget();

private:
    void createNodesAndEdges(QGraphicsScene *scene);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;

signals:

public slots:
};

#endif // STORYGRAPHWIDGET_H
