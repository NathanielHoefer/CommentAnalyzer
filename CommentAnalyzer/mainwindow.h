#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <list>

using std::list;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStringList mFiles;
    int mCommentIndex;
    QStringList mComments;

    void parseComments();


private slots:
    void selSrcFiles();
//    void loadText();
//    void nextComment();
//    void previousComment();
};

#endif // MAINWINDOW_H
