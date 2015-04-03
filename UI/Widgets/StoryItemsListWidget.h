#ifndef STORYITEMSLISTWIDGET_H
#define STORYITEMSLISTWIDGET_H

#include <QWidget>
#include <QListView>

class StoryManager;
class SituationListModel;
class ChoiceListModel;
class Situation;
class Choice;

class StoryItemsListWidget : public QWidget
{
    Q_OBJECT

    StoryManager *m_StoryManager;
    QListView *m_ChoicesListView;
    QListView *m_SituationsListView;

    SituationListModel *m_SituationListModel;
    ChoiceListModel *m_ChoiceListModel;

public:
    explicit StoryItemsListWidget(StoryManager *storyManager, QWidget *parent = 0);
    ~StoryItemsListWidget();

signals:
    void situationClicked(Situation *situation);
    void choiceClicked(Choice *choice);

public slots:
    void markSituationAsSelected(Situation *situation);
    void markChoiceAsSelected(Choice *choice);

private slots:
    void situationClicked(const QModelIndex &modelIndex);
    void choiceClicked(const QModelIndex &modelIndex);
};

#endif // STORYITEMSLISTWIDGET_H
