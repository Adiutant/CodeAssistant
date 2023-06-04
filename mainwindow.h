
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbhelper/dbhelper.h"
#include <QToolBar>
#include "widgets/nestedlist.h"
#include "codesnippetview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    NestedList *getDataList() const;
    void setDataList(NestedList *newDataList);

private:
    Ui::MainWindow *ui;
    NestedList *dataList;
    DbHelper *dbHelper;
    QToolBar *topToolBar;
    QAction *backAction;
    CodeSnippetView *view;
    int prevId;
    void showCodeSnippet(NestedItem, bool);
private slots:
    void onLoadNextItems(int id);
    void onLoadData(int id);
    void onNewItemRequest();
    void onBackAction();


};

#endif // MAINWINDOW_H
