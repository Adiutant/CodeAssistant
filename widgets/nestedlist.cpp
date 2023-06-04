
#include "nestedlist.h"

NestedList::NestedList(const QVector<NestedItem> &items)
{
    reloadData(items);
}

void NestedList::reloadData(const QVector<NestedItem> &items)
{
    clear();
    if (items.empty()){
        auto hLay =  new  QHBoxLayout () ;

        auto newButton =  new QPushButton ( "Добавить элемент" ) ;
        connect(newButton, &QPushButton::clicked,this,[=]{ emit newItemRequest();} );

        hLay->addWidget ( newButton ) ;

        auto buttonWidget =  new  QWidget (this ) ;
        buttonWidget-> setLayout ( hLay ) ;
        auto listItem = new  QListWidgetItem ( this) ;
        listItem->setSizeHint(QSize(this->width()-10,50));
        setItemWidget(listItem,buttonWidget);
        return;
    }
    for (const auto &item : items){
        auto psw = new NestedListWidget(item);
        auto listItem = new  QListWidgetItem ( this) ;
        listItem->setSizeHint(QSize(this->width()-10,70));
        connect(this, &QListWidget::itemClicked,this, &NestedList::onItemClicked );
        connect(psw,&NestedListWidget::changeRequest, this,&NestedList::onChangeRequest );
        setItemWidget(listItem,psw);
    }
    if (items.at(0).m_type ==  EntityType::Root){
        return;
    }
    auto hLay =  new  QHBoxLayout () ;

    auto newButton =  new QPushButton ( "Добавить элемент" ) ;
    connect(newButton, &QPushButton::clicked,this,[=]{ emit newItemRequest();} );
    hLay->addWidget ( newButton ) ;

    auto buttonWidget =  new  QWidget (this ) ;
    buttonWidget-> setLayout ( hLay ) ;
    auto listItem = new  QListWidgetItem ( this) ;
    listItem->setSizeHint(QSize(this->width()-10,50));
    setItemWidget(listItem,buttonWidget);


}

void NestedList::onItemClicked(QListWidgetItem *item)
{
    disconnect(this, &QListWidget::itemClicked,this, &NestedList::onItemClicked );
    auto widgetLink = itemWidget(item);
    auto widget =  dynamic_cast<NestedListWidget*>(widgetLink);
    switch (widget->item().m_type) {
    case EntityType::Root:

        emit loadNextItems(widget->item().m_id);
        break;
    case EntityType::Category:
        emit loadNextItems(widget->item().m_id);
        break;
    default:
        emit loadData(widget->item().m_id);
    }
    connect(this, &QListWidget::itemClicked,this, &NestedList::onItemClicked );

}

void NestedList::onChangeRequest(int id)
{
    emit loadData(id);
}

