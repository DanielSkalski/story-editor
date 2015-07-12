#ifndef STORYEXPORTERBASE_H
#define STORYEXPORTERBASE_H

#include <QObject>

class StoryExporterBase : public QObject
{
    Q_OBJECT

public:
    explicit StoryExporterBase(QObject *parent = 0);
    virtual ~StoryExporterBase();

signals:

public slots:
};

#endif // STORYEXPORTERBASE_H
