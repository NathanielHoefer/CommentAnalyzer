#include "linecomment.h"

LineComment::LineComment() : Comment()
{
    // Intentionally left blank
}

LineComment::LineComment(QString text, QPair<int, int> lineNum, int colNum, bool badCom) :
    Comment(text, lineNum, colNum, badCom)
{
    // Intentionally left blank
}

QString LineComment::toString()
{
    return QStringLiteral("Type: ") + getType() + QStringLiteral(", ") + Comment::toString();
}

Comment * LineComment::merge(Comment *com)
{
    if (this->getType() == com->getType()) {
        Comment::merge(com);
        delete com;
    }
    return this;
}
