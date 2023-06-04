
#ifndef NESTEDLISTWIDGET_H
#define NESTEDLISTWIDGET_H

#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFile>


enum EntityType{
    Class,
    Function,
    Struct,
    Enum,
    Category,
    Root
};

struct NestedItem{
    QString m_name;
    QString m_file;
    QString m_description;
    EntityType m_type;
    QVector<NestedItem> m_childs;
    int m_id;
    int m_parentId;
    NestedItem(const NestedItem &);
    NestedItem();
    NestedItem(QString, QString, QString, EntityType, QVector<NestedItem>, int id, int parentId);

};

class NestedListWidget : public QWidget
{
    Q_OBJECT
public:
    NestedListWidget();
    NestedListWidget(NestedItem item);
    NestedItem item() const;
signals:
    void changeRequest(int );


private:
    NestedItem m_item;
    void initializeGui();

};

#endif // NESTEDLISTWIDGET_H
