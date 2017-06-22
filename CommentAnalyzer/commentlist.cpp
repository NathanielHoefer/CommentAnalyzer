#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QCoreApplication>
#include <QDomDocument>
#include <QTextStream>
#include "commentlist.h"


static const QString XML_DIR = QStringLiteral("xml_files");
static const QString TEMP_SRCML_PATH = "G:\\Google Drive\\03. School\\02. Wichita State University\\03_Summer_2017\\05_Undergraduate_Research\\Research\\srcML\\srcML 1.0.0\\bin\\srcml.exe";

namespace {

    /*  Parses the file name from a file path
     */
    QString parseFileName(const QString &path) {
        int startInd = path.lastIndexOf('/') + 1;
        int nameLen = path.length() - startInd;
        return path.mid(startInd, nameLen);
    }

}

CommentList::CommentList() :
    mFilePath(""),
    mFileName(""),
    mXmlPath(""),
    mLastUpdateTime(QDate()),
    mCount(0)
{
    // Intentionally left blank
}

CommentList::CommentList(QString filePath)
{
    mFilePath = QDir::fromNativeSeparators(filePath);
    mFileName = parseFileName(mFilePath);
    mXmlPath = "";
    mLastUpdateTime = QFileInfo(mFilePath).lastModified();
    mCount = 0;
}

CommentList::~CommentList()
{

}

QString CommentList::getFilePath() const
{
    return mFilePath;
}

QString CommentList::getFileName() const
{
    return mFileName;
}

QDateTime CommentList::getLastUpdateTime() const
{
    return mLastUpdateTime;
}

int CommentList::getCount() const
{
    return mCount;
}

void CommentList::setFilePath(const QString &path)
{
    mFilePath = path;
    mFileName = parseFileName(mFilePath);
    mXmlPath = "";
    mLastUpdateTime = QFileInfo(mFilePath).lastModified();
    mCount = 0;
}

void CommentList::import() throw (std::invalid_argument)
{
    convertSrcToXml();
    importCommentFromXml();
}

QString CommentList::toString()
{
    QStringList output;
    output << QString("File Name: %1").arg(mFileName);
    output << QString("File Path: %1").arg(mFilePath);
    output << QString("XML Path: %1").arg(mXmlPath);
    output << QString("Date Modified: %1").arg(mLastUpdateTime.toString());
    output << QString("Comment Count: %1").arg(mCount);
    return output.join("\n") + "\n";
}

void CommentList::convertSrcToXml() throw (std::invalid_argument)
{
    if (mFileName == "") {
        return;
    }

    QStringList arguments;

    // Enters xml directory
    QDir directory(QCoreApplication::applicationDirPath());
    directory.cdUp();
    if (!directory.cd(XML_DIR)) {
        directory.mkdir(XML_DIR);
        directory.cd(XML_DIR);
    }

    // Formats new xml absolute path
    mXmlPath = mFileName.replace(".", "_");
    mXmlPath.append(".xml");
    mXmlPath.prepend(directory.absolutePath() + '/');

    // Executes srcML to convert the current source file to the
    arguments << QDir::toNativeSeparators(mFilePath) << QStringLiteral("-o") << QDir::toNativeSeparators(mXmlPath);

    QProcess *srcml = new QProcess();
    QString srcmlPath = TEMP_SRCML_PATH;
    srcml->start(srcmlPath, arguments);
}

void CommentList::importCommentFromXml() throw (std::invalid_argument)
{
    QDomDocument doc;
    QFile file(mXmlPath);

    QFile output("C:\\Users\\natha\\Documents\\OutputLogs\\logs.txt");
    if (!output.open(QFile::WriteOnly)) return;
    QTextStream out(&output);

    if (!file.open(QFile::ReadOnly) || !doc.setContent(&file)) return;

    QDomNodeList comments = doc.elementsByTagName("comment");
    for (int i = 0; i < (int) comments.size(); i++) {
        QDomNode codeLine = comments.item(i).nextSibling();

        // Comment Text and Line Numbers
        QString nextElem = codeLine.nodeName();
        out << QString("Comment %1: ").arg(i) << endl;
        int curLine = comments.item(i).lineNumber() - 1;
        int nextLine = comments.item(i).firstChild().lineNumber() - 1;
        out << QString("Com Start Line: %1, End Line: %2").arg(curLine).arg(nextLine) << endl;

        // Print comment map
        QMap<int, QString> comMap = domCommentNodeToMap(comments.item(i));
        for (QMap<int, QString>::const_iterator i = comMap.begin(); i != comMap.end(); i++) {
            out << QString("Line %1: %2").arg(i.key()).arg(i.value()) << endl;
        }

        // Following Line Info
        int codeStartLine = codeLine.lineNumber() - 1;
        int codeEndLine = codeLine.nextSibling().lineNumber() - 1;
        out << QString("Code Lines: %1").arg(codeLine.nodeName()) << endl;
        out << QString("Code Lines Numbers: %1 - %2").arg(codeStartLine).arg(codeEndLine) << endl;

        if (curLine + 1 == nextLine) {
            out << QString("   Next Sibling: %1").arg(nextElem) << endl;
            out << QString("   End Line Num: %1").arg(codeLine.nextSibling().lineNumber()) << endl;
        }
        out << endl;
    }

    output.close();
    file.close();
}

QMap<int, QString> CommentList::domCommentNodeToMap(const QDomNode &parent)
{
    int startLine = parent.lineNumber() - 1;
    QMap<int, QString> map;
    QStringList text = parent.firstChild().nodeValue().split("\n");

    for (int i = startLine; !text.isEmpty(); i++) {
        map[i] = text.front();
        text.pop_front();
    }

    return map;
}


