//==============================================================================
// Comment Analyzer - Line Comment Class
//==============================================================================
/*
    File: linecomment.h
    Project: Comment Analyzer
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Date: 6/13/2017

    Extends the comment class which contains the comment data after being
    parsed from the XML file with the addition of clarifying what type of
    of comment it is.

******************************************************************************/

#ifndef LINECOMMENT_H
#define LINECOMMENT_H

#include <QString>
#include "comment.h"

class LineComment : public Comment
{
public:
    LineComment();
    LineComment(QString text, QPair<int, int> lineNum, int colNum, bool badCom);

    virtual QString getType() { return QStringLiteral("Line"); }
    QString toString();

    /*  Combines the entered comment with the current one if they are
     *  within the same column, the entered comment is on the following line,
     *  and the comments are of the same type. Also will delete the following
     *  comment if successful
     *      Returns: The combined comment if conditions are met, otherwise
     *          the calling comment is returned
     */
    virtual Comment * merge(Comment *com);
};

#endif // LINECOMMENT_H
