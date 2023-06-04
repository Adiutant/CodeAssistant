#ifndef CODESNIPPETVIEW_H
#define CODESNIPPETVIEW_H

#include <QWidget>
#include "widgets/nestedlistwidget.h"
#include "dbhelper/dbhelper.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDialog>

namespace Ui {
class CodeSnippetView;
}

class CodeSnippetView : public QDialog
{
    Q_OBJECT

public:
    explicit CodeSnippetView(QWidget *parent = nullptr);
    void loadData(NestedItem item);
    void setDbConnector(DbHelper *dbHelper);
    ~CodeSnippetView();

    int getPrevId() const;

    void setPrevId(int newPrevId);

private:
    void saveData();
    bool newSnippet = true;
    DbHelper *m_dbHelper;
    int prevId;
    int currId=0;
    QByteArray source;
    QByteArray header;
    void saveToFile(const QString& path);
    void loadFromFile(const QString& path);
    Ui::CodeSnippetView *ui;
};

#endif // CODESNIPPETVIEW_H
