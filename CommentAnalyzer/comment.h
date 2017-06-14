//==============================================================================
// Comment Analyzer - Comment Class
//==============================================================================
/*
    File: comment.h
    Project: Comment Analyzer
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Date: 6/13/2017

    Contains the comment data after being parsed from the XML file

******************************************************************************/

#ifndef COMMENT_H
#define COMMENT_H

#include <QString>
#include <QPair>
#include <list>

class Comment
{
public:

    // Constructors/Destructors
    Comment();
    Comment(QString text, QPair<int, int> lineNum, int colNum, bool badCom);
    virtual ~Comment();

    // Accessors/Mutators
    QString getText() const;
    QPair<int, int> getLineNumbers() const;
    int getColumnNumber() const;
    bool isBadComment() const;

    void setBadComment(bool isBad);

    /*  Combines the entered comment with the current one if they are
     *  within the same column, the entered comment is on the following line.
     *  Also will delete the following comment if successful
     *      Returns: The combined comment if conditions are met, otherwise
     *          the calling comment is returned
     */
    virtual Comment * merge(const Comment *com);

    /*  Return the type of the comment.
     */
    virtual QString getType() = 0;

    /*  Converts the member variables to strings separated by titles and ", "
     */
    QString toString();

private:
    QString mText;
    QPair<int, int> mLineNumbers;
    int mColumnNumber;
    bool mBadComment;
};

#endif // COMMENT_H
