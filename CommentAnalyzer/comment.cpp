#include "comment.h"
#include <QStringList>

Comment::Comment()
{
    mText = "";
    mLineNumbers = QPair<int, int>(0, 0);
    mColumnNumber = 0;
    mBadComment = false;
}

Comment::Comment(QString text, QPair<int, int> lineNum, int colNum, bool badCom) :
    mText(text), mLineNumbers(lineNum), mColumnNumber(colNum), mBadComment(badCom)
{
    mColumnNumber = colNum >= 0 ? colNum : 0;
    mLineNumbers.second = lineNum.second >= 0 ? lineNum.second : 0;
    mLineNumbers.first = (lineNum.first >= 0 && lineNum.first <= lineNum.second) ? lineNum.first : 0;
}

Comment::~Comment()
{
    // Intentionally left blank
}

QString Comment::getText() const
{
    return mText;
}

QPair<int, int> Comment::getLineNumbers() const
{
    return mLineNumbers;
}

int Comment::getColumnNumber() const
{
    return mColumnNumber;
}

bool Comment::isBadComment() const
{
    return mBadComment;
}

void Comment::setBadComment(bool isBad)
{
    mBadComment = isBad;
}

Comment * Comment::merge(const Comment *com)
{
    int lineSeparation = com->getLineNumbers().first - this->getLineNumbers().second;
    if (lineSeparation == 1 && this->getColumnNumber() == com->getColumnNumber()) {
        mLineNumbers.second = com->mLineNumbers.second;
        mText += "\n" + com->mText;
    }
    return this;
}

QString Comment::toString()
{
    QStringList output;
    output << "Text: " + mText
           << "Start Line: " + QString::number(mLineNumbers.first)
           << "Ending Line: " + QString::number(mLineNumbers.second)
           << "Column Number: " + QString::number(mColumnNumber)
           << "Bad comment: " + QString::number(mBadComment);
    return output.join(", ");
}
