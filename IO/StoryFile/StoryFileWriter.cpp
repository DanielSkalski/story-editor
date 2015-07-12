#include "StoryFileWriter.h"

#include "Model/Story.h"
#include "Model/Situation.h"
#include "Model/Choice.h"

#include <QTextStream>
#include <QFile>

StoryFileWriter::StoryFileWriter(QObject *parent) : QObject(parent)
{

}

StoryFileWriter::~StoryFileWriter()
{

}

void StoryFileWriter::write(const QString& filepath, Story *story)
{
    QFile file(filepath);

    if (file.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream fileStream(&file);
        serialize(fileStream, story);

        file.close();
    }
}

void StoryFileWriter::serialize(QTextStream &out, Story * story) const
{
    out << "{" << endl;
    out << "\t" << "\"situations\" : [" << endl;

    Situation *last = story->situations().last();

    for (Situation *situation : story->situations())
    {
        out << "\t\t" << "{" << endl;

        out << "\t\t\t" << "\"id\" : \"" << situation->id() << "\"," << endl;
        out << "\t\t\t" << "\"title\" : \"" << situation->title() << "\"," << endl;
        out << "\t\t\t" << "\"content\" : \"" << situation->content() << "\"," << endl;
        out << "\t\t\t" << "\"x\" : " << situation->position.x() << "," << endl;
        out << "\t\t\t" << "\"y\" : " << situation->position.y() << "" << endl;

        out << "\t\t" << "}";

        if (situation != last)
        {
            out << ",";
        }

        out << endl;
    }

    out << "\t" << "]" << endl;

    out << "}" << endl;
}
