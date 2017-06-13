#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QProcess>
#include <QDebug>

static const QString SOURCE_DIR = "G:\\Google Drive\\03. School\\02. Wichita State University\\03_Summer_2017\\05_Undergraduate_Research\\03_Project\\01_TestFiles";
static const QString XML_DIR = QStringLiteral("xml_files");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionSelectSourceFiles, SIGNAL(triggered()), this, SLOT(selSrcFiles()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::parseComments()
{
    QStringList arguments;

    // Convert each file to xml and save within the xml folder
    foreach (const QString &fileName, mFiles) {
        QFile file(fileName);
        QDir directory(QCoreApplication::applicationDirPath());
        directory.cdUp();

        // Enters xml directory
        if (!directory.cd(XML_DIR)) {
            directory.mkdir(XML_DIR);
            directory.cd(XML_DIR);
        }

        // Formats new path
        QString newFileName = file.fileName();
        int startInd = newFileName.lastIndexOf('/') + 1;
        int nameLen = newFileName.lastIndexOf('.') - startInd; // Index of '.' from right

        newFileName = newFileName.mid(startInd, nameLen);

        qDebug() << newFileName << endl;

        newFileName.append(QStringLiteral(".xml"));
        newFileName.prepend(directory.path() + "/");

        qDebug() << newFileName;

        arguments << fileName << QStringLiteral("-o") << newFileName;

        QProcess *srcml = new QProcess(this);
        QString tempPath = "G:\\Google Drive\\03. School\\02. Wichita State University\\03_Summer_2017\\05_Undergraduate_Research\\Research\\srcML\\srcML 1.0.0\\bin\\srcml.exe";
        srcml->start(tempPath, arguments);
    }
}

void MainWindow::selSrcFiles()
{

    mFiles = QFileDialog::getOpenFileNames(this,
        tr("Select Source Files"),
        //QDir::currentPath(),
        SOURCE_DIR,
        tr("Source Files (*.cpp *.h *.hpp *.txt)"));

//    qDebug() << QCoreApplication::applicationDirPath() << endl;
//    for (QStringList::iterator i = mFiles.begin(); i != mFiles.end(); i++) {
//        qDebug() << *i << endl;
//    }
    parseComments();
}
