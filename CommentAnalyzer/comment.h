#ifndef COMMENT_H
#define COMMENT_H

#include <QString>
#include <QPair>
#include <list>

class Comment
{
public:
    Comment();
    Comment(QString text, QPair lineNum, int colNum, bool badCom);
    virtual ~Comment();

    // Accessors
    QString getText() const;
    QPair getLineNumbers() const;
    int getColumnNumber() const;
    bool isBadComment() const;

    // Mutators
    void setBadComment(bool isBad);

    /*  Combines the entered comment with the current one if they are
     *  within the same column and the entered comment is on the next line.
     *      Returns: The combined comment if conditions are met, otherwise
     *          the calling comment is returned
     */
    Comment merge(const Comment &com);

private:
    QString mText;
    QPair mLineNumbers;
    int mColumnNumber;
    bool mBadComment;
};

#endif // COMMENT_H
