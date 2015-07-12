#ifndef STORYFILEREADER_H
#define STORYFILEREADER_H

#include <QObject>

class Story;

class StoryFileReader : public QObject
{
    Q_OBJECT
public:
    explicit StoryFileReader(QObject *parent = 0);
    ~StoryFileReader();

    Story read(const QString &filepath);

signals:

public slots:
};

#endif // STORYFILEREADER_H
