
#include <QTextStream>
#include "commenttestdriver.h"

static const QString SOURCE_TEST_PATH_1 = "G:\\Google Drive\\03. School\\02. Wichita State University\\03_Summer_2017\\05_Undergraduate_Research\\03_Project\\01_TestFiles\\rotateParseTest.cpp";
static const QString OUTPUT_LOGS = "C:\\Users\\natha\\Documents\\OutputLogs\\logs.txt";

CommentTestDriver::CommentTestDriver()
{

}

void CommentTestDriver::testComment()
{
//    QString comText1;
//    Comment comParent1();

    CommentList list1(SOURCE_TEST_PATH_1);
    list1.import();
    QFile logFile(OUTPUT_LOGS);
    if (!logFile.open(QFile::WriteOnly)) {
        return;
    }
    QTextStream out(&logFile);
    out << list1.toString();
}
