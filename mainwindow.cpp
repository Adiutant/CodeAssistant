
#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PROJECT_NAME "CodeAssistaint"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(PROJECT_NAME);
    if (!QDir("code").exists())
    {
        QDir().mkdir("code");
    }
    dbHelper = new DbHelper();
    topToolBar = new QToolBar();
    backAction =new QAction("Назад");
    backAction->setEnabled(false);
    connect(backAction, &QAction::triggered,this, &MainWindow::onBackAction);
    topToolBar->addAction(backAction);
    addToolBar(Qt::TopToolBarArea, topToolBar);
    dataList =  new NestedList(dbHelper->getRoot());
    dataList->setFixedSize(size());
    ui->mainLayout->addWidget(dataList);
    connect(dataList, &NestedList::newItemRequest, this, &MainWindow::onNewItemRequest);
    connect(dataList, &NestedList::loadNextItems, this, &MainWindow::onLoadNextItems);
    connect(dataList, &NestedList::loadData, this, &MainWindow::onLoadData);

    setFixedSize(size());


}

MainWindow::~MainWindow()
{
    delete ui;
}

NestedList *MainWindow::getDataList() const
{
    return dataList;
}

void MainWindow::setDataList(NestedList *newDataList)
{
    dataList = newDataList;
}

void MainWindow::showCodeSnippet(NestedItem item , bool isNew)
{
    view =new CodeSnippetView();
    view->setPrevId(prevId);
    if (!isNew){
        view->loadData(item);
    }
    if(view->exec()){
        auto prevParent = dbHelper->getById(prevId);
        dataList->reloadData(prevParent.m_childs);
    }

    delete view;
}

void MainWindow::onLoadNextItems(int id)
{
    dataList->reloadData(dbHelper->getById(id).m_childs);
    backAction->setEnabled(true);
    prevId = id;
}

void MainWindow::onLoadData(int id)
{
    auto item = dbHelper->getById(id);
    prevId = item.m_parentId;
    backAction->setEnabled(true);
    showCodeSnippet(item,false);

}

void MainWindow::onNewItemRequest()
{
    showCodeSnippet(NestedItem{}, true);

}

void MainWindow::onBackAction()
{
    auto prevParentId = dbHelper->getById(prevId).m_parentId;
    if(prevParentId == 0){
        dataList->reloadData(dbHelper->getRoot());
        backAction->setEnabled(false);
        return;
    }
    auto prevParent = dbHelper->getById(prevParentId);
    dataList->reloadData(prevParent.m_childs);
    prevId = prevParent.m_id;

}



