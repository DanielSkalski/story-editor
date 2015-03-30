#include "ItemPropertiesWidget.h"

#include "Model/Situation.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>

ItemPropertiesWidget::ItemPropertiesWidget(QWidget *parent) : QWidget(parent)
{
    m_IdEdit = new QLineEdit(this);
    m_TitleEdit = new QLineEdit(this);
    m_ContentEdit = new QTextEdit(this);

    QLabel* idLabel = new QLabel("Id", this);
    QLabel* titleLabel = new QLabel("Title", this);
    QLabel* contentLabel = new QLabel("Content", this);

    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->addWidget(idLabel, 0, 0);
    gridLayout->addWidget(m_IdEdit, 0, 1);
    gridLayout->addWidget(titleLabel, 1, 0);
    gridLayout->addWidget(m_TitleEdit, 1, 1);
    gridLayout->addWidget(contentLabel, 2, 0, 1, 2);
    gridLayout->addWidget(m_ContentEdit, 3, 0, 1, 2);

    setMinimumSize(300, 100);

    setLayout(gridLayout);
}

ItemPropertiesWidget::~ItemPropertiesWidget()
{

}

void ItemPropertiesWidget::selectedSituationChanged(Situation *situation)
{
    if (m_CurrentSituation != nullptr)
    {
        m_IdEdit->disconnect(m_CurrentSituation);
        m_TitleEdit->disconnect(m_CurrentSituation);
        m_ContentEdit->disconnect(m_CurrentSituation);
    }

    m_CurrentSituation = situation;

    if (situation != nullptr)
    {
        m_IdEdit->setText(situation->id());
        m_TitleEdit->setText(situation->title());
        m_ContentEdit->setText(situation->content());

        connect(m_IdEdit, SIGNAL(textChanged(QString)), m_CurrentSituation, SLOT(setId(QString)));
        connect(m_TitleEdit, SIGNAL(textChanged(QString)), m_CurrentSituation, SLOT(setTitle(QString)));
        connect(m_ContentEdit, &QTextEdit::textChanged, [&]
        {
            m_CurrentSituation->setContent(m_ContentEdit->toPlainText());
        });
    }
}
