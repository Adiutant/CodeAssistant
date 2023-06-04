#include "codesnippetview.h"
#include "ui_codesnippetview.h"

CodeSnippetView::CodeSnippetView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CodeSnippetView)
{
    ui->setupUi(this);
    ui->typePicker->addItem("Класс");
    ui->typePicker->addItem("Функция");
    ui->typePicker->addItem("Структура");
    ui->typePicker->addItem("Перечисление");
    ui->typePicker->addItem("Категория");
    connect(ui->saveButton, &QPushButton::clicked, this, &CodeSnippetView::saveData);
}

void CodeSnippetView::loadData(NestedItem item)
{
    ui->nameEdit->setText(item.m_name);

    ui->typePicker->setCurrentIndex(item.m_type);

    ui->descriptionEdit->setPlainText(item.m_description);
    loadFromFile(item.m_file);
    currId = item.m_id;

    newSnippet = false;

}

void CodeSnippetView::setDbConnector(DbHelper *dbHelper)
{
    if (m_dbHelper == nullptr){
        m_dbHelper = dbHelper;
    }
}

CodeSnippetView::~CodeSnippetView()
{
    delete ui;
}

void CodeSnippetView::saveData()
{

    auto name = ui->nameEdit->text();
    auto hash = QDateTime::currentDateTime().toMSecsSinceEpoch();
    auto fileName =  QString("code/%1%2.code").arg(name, QString::number(hash));
    auto item = NestedItem{ui->nameEdit->text(), fileName, ui->descriptionEdit->toPlainText(),
                           static_cast<EntityType>(ui->typePicker->currentIndex()), QVector<NestedItem>(),currId,prevId};
    if (item.m_type == EntityType::Category){
        item.m_file = "";
    }
    auto isSave = m_dbHelper->save(item, newSnippet);
    if(item.m_type == EntityType::Category){
        done(1);
        return;
    }
    if( isSave){
        saveToFile(item.m_file);

    }

}

void CodeSnippetView::saveToFile(const QString &path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadWrite)){
        QJsonDocument doc;
        QJsonObject obj;
        obj.insert("header", ui->codeEdit->toPlainText());
        obj.insert("source", ui->codeEditSrc->toPlainText());
        doc.setObject(obj);
        file.write(doc.toJson());
        file.close();
        done(1);
    }
}

void CodeSnippetView::loadFromFile(const QString &path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadWrite)){
        auto data =  file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        auto obj = doc.object();
        if (obj.contains("source")){
            auto value = obj.value("source");
            ui->codeEdit->setPlainText(value.toString());
        }
        if (obj.contains("header")){
            auto value = obj.value("header");
            ui->codeEditSrc->setPlainText(value.toString());
        }

        file.close();
    }

}

void CodeSnippetView::setPrevId(int newPrevId)
{
    prevId = newPrevId;
}

int CodeSnippetView::getPrevId() const
{
    return prevId;
}
