//==============================================================================
// Comment Analyzer - Comment Class
//==============================================================================
/*
    File: comment.h
    Project: Comment Analyzer
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Date: 6/13/2017

    This class contains the information of a comment listed in a source file.
    The data includes:
        Comment Text: The text that is listed in the comment
        Code Text: The text of the code being described by the comment. This
            should only describe code directly after or on the same line
            as the comment
        Line Numbers: The starting and ending line number of the comment
        Type: Describes what type of comment it is. See enum Type below
        Format: Enum describing the comment as either a line comment or block
        Parent/Children: This class acts as nodes so requires pointers to
            the parent comment and any children.

     TODO: Restructure class to act as node.
     TODO: Remove additional derived comment classes

******************************************************************************/

#ifndef COMMENT_H
#define COMMENT_H

#include <QString>
#include <QPair>
#include <list>

class Comment
{
public:


    /**
     * @brief Identifies the type of comment
     * Header: The first comment of the document with description info.
     * Class: Comment directly preceding a class definition.
     * Function: Comment directly preceding a function definition or declaration.
     * Associated: A comment associated with a specific line of code. Can be directly
     *      preceding or next to a line of code that is not one of the types above.
     * Independent: Comment neither directly preceding or next to a line of code.
     */
    enum Type { Header, Class, Function, Associated, Independent };
    enum Format { Line, Block };

    // Constructors/Destructors
    Comment();
    Comment(const QString &comText, const QString &codeText,
            const QPair<int, int> &lineNum, Type type, Format format, bool badCom);
    virtual ~Comment();

    // Accessors/Mutators
    QString getText() const;
    QPair<int, int> getLineNumbers() const;
    bool isBadComment() const;

    void setBadComment(bool isBad);

    /**
     * Combines the entered comment with the current one if they are
     *  within the same column, the entered comment is on the following line.
     *  Also will delete the following comment if successful
     *      Returns: The combined comment if conditions are met, otherwise
     *          the calling comment is returned
     */
    Comment * merge(const Comment *com);

    /**
     * Return the type of the comment.
     */
    QString getType();

    /**
     * Converts the member variables to strings separated by titles and ", "
     */
    QString toString();

private:
    Comment *mParentComment;
    list<Comment*> mChildrenComments;
    QString mCommentText;
    QString mCodeText;
    QPair<int, int> mLineNums;
    Type mType;
    Format mFormat;
    bool mBadComment;
};

#endif // COMMENT_H
