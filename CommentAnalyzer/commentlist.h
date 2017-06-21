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

#include <QVector>
#include <QDateTime>
#include "comment.h"

class CommentList
{
public:

//==============================================================================
// CONSTRUCTORS / DESTRUCTORS
//==============================================================================

    // TODO: Testing
    CommentList();
    CommentList(QString filePath);
    ~CommentList();

//==============================================================================
// ACCESSORS / MUTATORS
//==============================================================================

    /** TODO
     * @brief getFilePath
     * @return Returns the file path of the source file
     */
    QString getFilePath() const;

    /** TODO
     * @brief getFileName
     * @return Returns the file name of the source file
     */
    QString getFileName() const;

    /** TODO
     * @brief getLastUpdateTime
     * @return Returns the timestamp of the last update to the source file
     */
    QDateTime getLastUpdateTime() const;

    /** TODO
     * @brief getCount
     * @return returns the number of comments found within the source file
     */
    int getCount() const;

    /** TODO
     * @brief setFilePath
     * @param path - the full file path to the source file
     */
    void setFilePath(const QString &path);

//==============================================================================
// PUBLIC MEMBER FUNCTIONS
//==============================================================================

    /** TODO
     *  Imports all of the comments from the source file specified.
     *  If there is an issue with importing, throws invalid_argument
     *  exception.
     */
    void import() throw (std::invalid_argument);

    /**
     * @brief toString
     * @return Returns string of all the member variables
     */
    QString toString();

private:

//==============================================================================
// MEMBER VARIABLES
//==============================================================================
    QVector<Comment*> mCommentList;     // List of all the root comments
    QString mFilePath;                  // Absolute file path of the source file
    QString mFileName;                  // Absolute file name of the source file
    QString mXmlPath;                   // Absolute path to the source xml file
    QDateTime mLastUpdateTime;          // Timestamp of last update to source
    int mCount;                         // Number of comments found

//==============================================================================
// PRIVATE MEMBER FUNCTIONS
//==============================================================================

    /** TODO
     *  Converts the source file into an xml file and stores it in
     *  a folder in the directory above the executable. The conversion
     *  is done using srcML
     */
    void convertSrcToXml() throw (std::invalid_argument);

    /** TODO
     *  Parses and imports the comment objects from the source xml file
     *  and adds them to the comment list.
     */
    void importCommentFromXml(const QString xmlPath) throw (std::invalid_argument);
};

#endif // COMMENTLIST_H
