#include "blockcomment.h"

BlockComment::BlockComment() : Comment()
{
    // Intentionally left blank
}

BlockComment::BlockComment(QString text, QPair<int, int> lineNum, int colNum, bool badCom) :
    Comment(text, lineNum, colNum, badCom)
{
    // Intentionally left blank
}

QString BlockComment::toString()
{
    return QStringLiteral("Type: ") + getType() + QStringLiteral(", ") + Comment::toString();
}

Comment *BlockComment::merge(Comment *com)
{
    if (this->getType() == com->getType()) {
        Comment::merge(com);
        delete com;
    }
    return this;
}
