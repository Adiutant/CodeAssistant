
#include "dbhelper.h"

DbHelper::DbHelper()
{
    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("code.db");

    if (!sdb.open()) {
        qDebug() << sdb.lastError().text();
        exit(-1);
    }
    qDebug () << sdb.tables().at(1);
}

DbHelper::~DbHelper()
{
    sdb.close();
}

NestedItem DbHelper::getById(int id)
{
    QSqlQuery res;
    res.exec(QString("SELECT * FROM entities WHERE id = %1;").arg(id));
    res.next();
    auto parentId = res.value("parent").toInt();
    auto name = res.value("name").toString();
    auto description = res.value("description").toString();
    auto fileLink = res.value("file").toString();
    auto type = res.value("type").toInt();
    res.clear();
    res.exec(QString("SELECT * FROM entities WHERE parent = %1;").arg(id));
    QVector<NestedItem> childs;
    if (type == EntityType::Category || type == EntityType::Root){
        while (res.next()) {
            auto childId = res.value("id").toInt();
            //auto childParentId = resChild.value("parent").toInt();
            auto childName = res.value("name").toString();
            auto childDescription = res.value("description").toString();
            auto childFileLink = res.value("file").toString();
            auto childType = res.value("type").toInt();
            auto nestedChild  = NestedItem{childName, childFileLink, childDescription,
                                          static_cast<EntityType>(childType), QVector<NestedItem>{},childId,id};
            childs.push_back(nestedChild);
        }
    }
    return NestedItem{name, fileLink, description, static_cast<EntityType>(type),childs,id,parentId};



}

bool DbHelper::save(NestedItem item , bool isNew)
{
    QSqlQuery res;
    if (isNew){
        res.exec(QString("INSERT INTO entities (parent, name, description, file, type) VALUES (%1,'%2','%3','%4',%5)")
                     .arg(QString::number(item.m_parentId), item.m_name, item.m_description, item.m_file, QString::number(item.m_type)));
    } else {
        res.exec(QString("UPDATE entities SET  parent = %1, name = '%2', description = '%3', file = '%4', type = %5 WHERE id = %6;")
                     .arg(QString::number(item.m_parentId), item.m_name, item.m_description, item.m_file, QString::number(item.m_type),QString::number(item.m_id)));
    }
    return res.lastError().text().isEmpty();
}

QVector<NestedItem> DbHelper::getRoot()
{
    QSqlQuery res;
    res.exec(QString("SELECT * FROM entities WHERE type = 5;"));
    QVector<NestedItem> roots;
    while (res.next()) {
        //auto childParentId = resChild.value("parent").toInt();
        auto name = res.value("name").toString();
        auto item =  NestedItem{};
        item.m_name = name;
        auto type =  res.value("type").toInt();
        item.m_type = static_cast<EntityType>(type);
        auto id = res.value("id").toInt();
        item.m_id = id;
        item.m_parentId =0;
        roots.push_back(item);
    }
    return roots;
}

