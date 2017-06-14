#include "commentlist.h"

namespace {

    /*  Parses the file name from a file path
     */
    QString parseFileName(const QString &path) {
        int startInd = path.lastIndexOf('/') + 1;
        int nameLen = path.lastIndexOf('.') - startInd;
        return path.mid(startInd, nameLen);
    }
}

CommentList::CommentList()
{

}
