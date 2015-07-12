#ifndef STORYFILEWRITER_H
#define STORYFILEWRITER_H

#include <QObject>

class Story;
class QTextStream;

class StoryFileWriter : public QObject
{
    Q_OBJECT
public:
    explicit StoryFileWriter(QObject *parent = 0);
    ~StoryFileWriter();

    void write(const QString &filepath, Story *story);

private:
    void serialize(QTextStream &out, Story *story) const;

signals:

public slots:
};

#endif // STORYFILEWRITER_H
