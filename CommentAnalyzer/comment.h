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

     TODO: Test current comment node structure
     TODO: Possibly create derived parent class and child comment class


******************************************************************************/

#ifndef COMMENT_H
#define COMMENT_H

#include <QString>
#include <QMap>
#include <QPair>
#include <QVector>

class Comment
{
public:

//==============================================================================
// ENUMERATIONS
//==============================================================================

    /**
     * @brief Identifies the type of comment
     * Header: The first comment of the document with description info.
     * Class: Comment directly preceding a class definition.
     * Function: Comment directly preceding a function definition or declaration.
     * Associated: A comment associated with a specific line of code. Can be directly
     *      preceding or next to a line of code that is not one of the types above.
     * Independent: Comment neither directly preceding or next to a line of code.
     */
    enum Type { Header, Class, Function, Associated, Independent, DefaultType };
    enum Format { Line, Block, DefaultFormat };

//==============================================================================
// CONSTRUCTORS / DESTRUCTORS
//==============================================================================

    Comment();

    /**
     * @brief This constructor is to create a child comment
     * @param parent
     * @param comLineNum
     * @param codeLineNum
     * @param type
     * @param format
     * @param badCom
     */
    Comment(Comment *parent,
            const QPair<int, int> &comLineNum,
            const QPair<int, int> &codeLineNum,
            Type type, Format format, bool badCom);

    /**
     * @brief This constructor is to create a root comment
     * @param comText
     * @param codeText
     * @param comLineNum
     * @param codeLineNum
     * @param type
     * @param format
     * @param badCom
     */
    Comment(const QString &comText,
            const QString &codeText,
            const QPair<int, int> &comLineNum,
            const QPair<int, int> &codeLineNum,
            Type type, Format format, bool badCom);

    virtual ~Comment();

//==============================================================================
// ACCESSORS / MUTATORS
//==============================================================================

    /**
     * @brief getParent
     * @return The pointer of the parent comment in which this comment is found
     */
    Comment * getParent();

    /**
     * @brief getChildren
     * @return a list of all the associated children found within the block
     * below this comment
     */
    QVector<Comment*> getChildren();

    /**
     * @brief getChild
     * @param index
     * @return The pointer of the child found at the specific index beginning
     * with zero. If child at index doesn't exist, then a null pointer is
     * returned.
     */
    Comment * getChild(int index);

    /**
     * @return The text found within the comment separated by line
     */
    QStringList getCommentText() const;

    /**
     * @return The text found within the code associated with the comment
     * separated by line
     */
    QStringList getCodeText() const;

    /**
     * @return The line numbers that the comment is found in. If the comment
     * is only one line long, then both numbers will be the same
     */
    QPair<int, int> getComLineNumbers() const;

    /**
     * @return The line numbers that the associated code is found in. If the
     * code is only one line long, then both numbers will be the same
     */
    QPair<int, int> getCodeLineNumbers() const;

    /**
     * @return The type of the comment (Header, Class, Function, Associated,
     * Independent)
     */
    Type getType() const;

    /**
     * @return The format of the comment (Line or Block)
     */
    Format getFormat() const;

    /**
     * @return True if the comment is found within defective code, otherwise
     * false.
     */
    bool isBadComment() const;

    /**
     * @brief Sets the parent of this comment to the entered comment
     * @param parent
     */
    void setParent(Comment * parent);

    /**
     * @brief setChild - Adds the child comment to the children list at
     * the specified location. If left blank, the child will be appended to
     * the end of the list.
     * @param child
     * @param index
     */
    void setChild(Comment * child, int index = -1);

    /**
     * @brief Labels the comment as either good or bad.
     * @param isBad - True if found within defective code
     */
    void setBadComment(bool isBad);

//==============================================================================
// PUBLIC MEMBER FUNCTIONS
//==============================================================================

    /**
     * Combines the entered comment with the current one if they are
     *  directly after each other, the entered comment is on the following line.
     *  Also will delete the following comment if successful
     * @return The combined comment if conditions are met, otherwise
     * the calling comment is returned
     */
    Comment * merge(const Comment *com);

    /**
     * Converts the member variables to strings separated by titles and ", "
     */
    QString toString();

private:

//==============================================================================
// MEMBER VARIABLES
//==============================================================================
    Comment *mParentComment;
    QVector<Comment*> mChildrenComments;
    QMap<int, QString> mText;           // Maps comment and code text by line number to be used by root parent comment
    QPair<int, int> mComLineNums;       // -1 indicates not initialized
    QPair<int, int> mCodeLineNums;      // -1 indicates no following code
    Type mType;
    Format mFormat;
    bool mBadComment;

//==============================================================================
// PRIVATE MEMBER FUNCTIONS
//==============================================================================

    /**
     * @brief getParentCodeText - To avoid having a lot of duplicate data, the
     * root comment will contain all of the code text to be used by the children.
     * @return The source code of the root comment separated by line number.
     */
    QMap<int, QString> getParentTextMap();

};

#endif // COMMENT_H
