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

private:
    void setupLayout();
    void setupChoicesListView();
    void setupSituationsListView();

signals:
    void situationClicked(Situation *situation);
    void choiceClicked(Choice *choice);

    void createSituationButtonClicked();
    void createChoiceButtonClicked();

public slots:
    void markSituationAsSelected(Situation *situation);
    void markChoiceAsSelected(Choice *choice);

    void addSituation(Situation *situation);
    void addChoice(Choice *choice);

    void onLoadedStory();

private slots:
    void onSituationClicked(const QModelIndex &modelIndex);
    void onChoiceClicked(const QModelIndex &modelIndex);

    void onCreateSituationButtonClicked();
    void onCreateChoiceButtonClicked();
};

#endif // STORYITEMSLISTWIDGET_H
