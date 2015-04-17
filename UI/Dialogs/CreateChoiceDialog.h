#ifndef CREATECHOICEDIALOG_H
#define CREATECHOICEDIALOG_H

#include <QDialog>

class Choice;
class Situation;
class StoryManager;
class ValidationResult;
class ChoiceValidator;

class QLineEdit;
class QTextEdit;
class QComboBox;
class QLabel;

class CreateChoiceDialog : public QDialog
{
    Q_OBJECT

    StoryManager *m_StoryManager;
    ChoiceValidator *m_ChoiceValidator;

    QPalette m_ErrorPalette;
    QPalette m_NormalPalette;

    QLabel *m_IdErrors;
    QLabel *m_SituationsErrors;

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

    Situation *getSelectedSituation(QComboBox *comboBox) const;
    Choice *createChoice() const;

    bool validateForm();
    bool validateId();
    bool validateSituations();

    void showSituationsValidationErrors(QList<QString> errors);
    void hideSituationsValidationErrors();

    void showIdValidationErrors(QString error);
    void hideIdValidationErrors();

private slots:
    void idEditTextChanged();
    void fromComboBoxSelectionChanged();
    void toComboBoxSelectionChanged();

    void createButtonClicked();
    void cancelButtonClicked();
};

#endif // CREATECHOICEDIALOG_H
