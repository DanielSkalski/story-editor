#ifndef CREATECHOICEDIALOG_H
#define CREATECHOICEDIALOG_H

#include <QDialog>

class Choice;
class Situation;
class StoryManager;
class QLineEdit;
class QTextEdit;
class QComboBox;

class CreateChoiceDialog : public QDialog
{
    Q_OBJECT

    StoryManager *m_StoryManager;

    Situation *m_From;
    Situation *m_To;
    Choice *m_CreatedChoice;

    QComboBox *m_FromComboBox;
    QComboBox *m_ToComboBox;

    QLineEdit *m_IdEdit;
    QTextEdit *m_ContentEdit;

    QPushButton *m_CreateButton;
    QPushButton *m_CancelButton;

public:
    explicit CreateChoiceDialog(StoryManager * storyManager, QWidget *parent = 0);
    ~CreateChoiceDialog();

private:
    void setupLayout();
    void populateComboBoxes();

signals:

private slots:
    void idEditTextChanged();
    void contentEditTextChanged();

    void createButtonClicked();
    void cancelButtonClicked();
};

#endif // CREATECHOICEDIALOG_H
