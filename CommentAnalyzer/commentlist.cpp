#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QCoreApplication>
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


