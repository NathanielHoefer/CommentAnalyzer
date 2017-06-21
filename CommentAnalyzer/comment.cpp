#include "comment.h"
#include <QStringList>

static const QString LINE_SEPARATOR = "\n";

namespace {

    /**
     * @brief mapToStringList - Converts the entered map to a string list
     * starting from the begin line number to the end line number
     * @param map
     * @param begin - starting line number
     * @param end - ending line number
     * @return a string list containing each line as its own element
     */
    QStringList mapToStringList(const QMap<int, QString> &map, int begin, int end) {
        QStringList output;
        int startOffset = begin - int(map.firstKey());
        int endOffset = int(map.lastKey()) - end;
        if (!map.empty() && startOffset >= endOffset) {
            for (QMap<int, QString>::const_iterator i = map.begin() + startOffset;
                i != map.end() - endOffset; i++) {
                output << *i;
            }
        }
        return output;
    }
}

Comment::Comment()
{
    mParentComment = NULL;
    mChildrenComments = QVector<Comment*>();
    mCommentText = QMap<int, QString>();
    mCodeText = QMap<int, QString>();
    mComLineNums = QPair<int, int>(-1, -1);
    mCodeLineNums = QPair<int, int>(-1, -1);
    mType = DefaultType;
    mFormat = DefaultFormat;
    mBadComment = false;
}

Comment::Comment(Comment *parent,
                 const QPair<int, int> &comLineNum,
                 const QPair<int, int> &codeLineNum,
                 Type type, Format format, bool badCom) :
    mParentComment(parent),
    mComLineNums(comLineNum),
    mCodeLineNums(codeLineNum),
    mType(type),
    mFormat(format),
    mBadComment(badCom)
{
    // Intentionally left blank
}

Comment::Comment(const QString &comText,
                 const QString &codeText,
                 const QPair<int, int> &comLineNum,
                 const QPair<int, int> &codeLineNum,
                 Type type, Format format, bool badCom) :
    mComLineNums(comLineNum),
    mCodeLineNums(codeLineNum),
    mType(type),
    mFormat(format),
    mBadComment(badCom)
{
    mParentComment = NULL;

    // Maps the comments text to the comment text map by line number
    QStringList tempComList = comText.split(LINE_SEPARATOR);
    for (int i = comLineNum.first; i <= comLineNum.second; i++) {
        mCommentText[i] = tempComList.front();
        tempComList.pop_front();
    }

    // Maps the code text to the code text map by line number
    QStringList tempCodeList = codeText.split(LINE_SEPARATOR);
    for (int i = codeLineNum.first; i <= codeLineNum.second; i++) {
        mCodeText[i] = tempCodeList.front();
        tempCodeList.pop_front();
    }
}

Comment::~Comment()
{
    // Intentionally left blank
}

Comment *Comment::getParent()
{
    return mParentComment;
}

QVector<Comment *> Comment::getChildren()
{
    return mChildrenComments;
}

Comment *Comment::getChild(int index)
{
    if (index >= 0 && index < mChildrenComments.size()) {
        return mChildrenComments[index];
    } else {
        return NULL;
    }
}

QStringList Comment::getCommentText() const
{
    if (mParentComment == NULL) {
        return mapToStringList(mCommentText, mComLineNums.first, mComLineNums.second);
    } else {
        return mapToStringList(mParentComment->getParentComTextMap(), mComLineNums.first, mComLineNums.second);
    }
}

QStringList Comment::getCodeText() const
{
    if (mParentComment == NULL) {
        return mapToStringList(mCodeText, mCodeLineNums.first, mCodeLineNums.second);
    } else {
        return mapToStringList(mParentComment->getParentCodeTextMap(), mCodeLineNums.first, mCodeLineNums.second);
    }
}

QPair<int, int> Comment::getComLineNumbers() const
{
    return mComLineNums;
}

QPair<int, int> Comment::getCodeLineNumbers() const
{
    return mCodeLineNums;
}

Comment::Type Comment::getType() const
{
    return mType;
}

Comment::Format Comment::getFormat() const
{
    return mFormat;
}

bool Comment::isBadComment() const
{
    return mBadComment;
}

void Comment::setParent(Comment *parent)
{
    mParentComment = parent;
}

void Comment::setChild(Comment *child, int index)
{
    if (index < 0 || index >= mChildrenComments.size()) {
        mChildrenComments.append(child);
    } else {
        mChildrenComments.insert(index, child);
    }
}

void Comment::setBadComment(bool isBad)
{
    mBadComment = isBad;
}

Comment * Comment::merge(const Comment *com)
{
    int lineSeparation = com->mComLineNums.first - this->mComLineNums.second;
    if (lineSeparation == 1
            && mType == com->mType
            && mCodeLineNums.first < 0
            && mParentComment == com->mParentComment) {
        mComLineNums.second = com->mComLineNums.second;
        mCodeLineNums = com->mCodeLineNums;
    }
    return this;
}

QString Comment::toString()
{
    QStringList output;
    output << "Comment Text: " + getCommentText().join("\n")
           << "Start Line: " + QString::number(mComLineNums.first)
           << "Ending Line: " + QString::number(mComLineNums.second)
           << "Code Text: " + getCodeText().join("\n")
           << "Bad comment: " + QString::number(mBadComment) + "\n\n";
    return output.join("\n");
}

QMap<int, QString> Comment::getParentComTextMap()
{
    if (mParentComment == NULL) {
        return mParentComment->mCommentText;
    } else {
        return mParentComment->getParentComTextMap();
    }
}

QMap<int, QString> Comment::getParentCodeTextMap()
{
    if (mParentComment == NULL) {
        return mParentComment->mCodeText;
    } else {
        return mParentComment->getParentCodeTextMap();
    }
}
