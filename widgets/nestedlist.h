
#ifndef NESTEDLIST_H
#define NESTEDLIST_H

#include <QListWidget>
#include "nestedlistwidget.h"
#include <QWidget>
#include <QPushButton>


class NestedList : public QListWidget
{
    Q_OBJECT
public:
    NestedList(const QVector<NestedItem> &items);
    void reloadData(const QVector<NestedItem> &items);
private slots:
    void onItemClicked(QListWidgetItem *item);
    void onChangeRequest(int);
signals:
    void loadNextItems(int);
    void loadData(int);
    void newItemRequest();
};

#endif // NESTEDLIST_H
