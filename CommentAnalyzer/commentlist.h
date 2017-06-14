//==============================================================================
// Comment Analyzer - Comment List Class
//==============================================================================
/*
    File: commentlist.h
    Project: Comment Analyzer
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Date: 6/13/2017

    A container for the comment objects which are imported using the the import
    function. Also contains data such as the number of comments, file name of
    the source file, and a timestamp of when the file was last updated.

******************************************************************************/

#ifndef COMMENTLIST_H
#define COMMENTLIST_H

#include <list>
#include <QDate>
#include "linecomment.h"
#include "blockcomment.h"

class CommentList
{
public:

    // Constructors/Destructors
    CommentList();
    CommentList(QString filePath);
    ~CommentList();

    // Accessors/Mutators
    QString getFilePath() const;
    QString getFileName() const;
    QDate getLastUpdateTime() const;
    int getCount() const;

    void setFilePath(const QString &path);


    /*  Imports all of the comments from the source file specified.
     *  If there is an issue with importing, throws invalid_argument
     *  exception.
     */
    void import() throw (std::invalid_argument);

private:
    std::list<Comment*> mCommentList;
    QString mFilePath;
    QString mFileName;
    QString mXmlPath;
    QDate mLastUpdateTime;
    int count;

    /*  Converts the source file into an xml file and stores it in
     *  a folder in the directory above the executable. The conversion
     *  is done using srcML
     *      Returns the file path of the xml file
     */
    QString convertSrcToXml() throw (std::invalid_argument);

    /*  Parses and imports the comment objects from the source xml file
     *  and adds them to the comment list.
     */
    void importCommentFromXml(const QString xmlPath) throw (std::invalid_argument);
};

#endif // COMMENTLIST_H
