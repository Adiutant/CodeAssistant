
#include "nestedlistwidget.h"
#include "qpushbutton.h"

NestedListWidget::NestedListWidget() : m_item{}
{
    initializeGui();
}

NestedListWidget::NestedListWidget(NestedItem item):
    m_item{item}
{
    initializeGui();

}

NestedItem NestedListWidget::item() const
{
    return m_item;
}

void NestedListWidget::initializeGui()
{
    auto   hLay =  new  QHBoxLayout () ;
    auto nameLabel = new QLabel(m_item.m_name);
    hLay->addWidget(nameLabel);
    if (m_item.m_type == EntityType::Category){
        auto changeButton = new QPushButton("Ред.");
        changeButton->setFixedSize(40,40);
        hLay->addWidget(changeButton);
        connect(changeButton, &QPushButton::clicked, this, [=]{emit changeRequest(m_item.m_id);});
    }
    auto mainWidget =  new QWidget(this);
    mainWidget->setLayout(hLay);

}


NestedItem::NestedItem(const NestedItem & another)
{
    m_name = another.m_name;
    m_file =another.m_file;
    m_description = another.m_description;
    m_type = another.m_type;
    m_childs = another.m_childs;
    m_id = another.m_id;
    m_parentId = another.m_parentId;


}

NestedItem::NestedItem()
{

}

NestedItem::NestedItem(QString name, QString file , QString description , EntityType type,
                       QVector<NestedItem> childs, int id, int parentId)
{
    m_name = name;
    m_file = file;
    m_description = description;
    m_type = type;
    m_childs = childs;
    m_id = id;
    m_parentId = parentId;



}


