#ifndef STORYITEMSLISTWIDGET_H
#define STORYITEMSLISTWIDGET_H

#include <QWidget>

class StoryManager;
class SituationListModel;
class ChoiceListModel;
class Situation;
class Choice;

class QPushButton;
class QListView;

class StoryItemsListWidget : public QWidget
{
    Q_OBJECT

    StoryManager *m_StoryManager;

    QListView *m_ChoicesListView;
    QListView *m_SituationsListView;
    QPushButton *m_CreateSituationButton;
    QPushButton *m_CreateChoiceButton;

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

    void addSituation(Situation *situation);
    void addChoice(Choice *choice);

private slots:
    void situationClicked(const QModelIndex &modelIndex);
    void choiceClicked(const QModelIndex &modelIndex);

    void createSituationButtonClicked();
    void createChoiceButtonClicked();
};

#endif // STORYITEMSLISTWIDGET_H
