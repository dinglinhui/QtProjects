#include <QSplitter>

#include "examinationwidget.h"
#include "borderlayout.h"
#include "dbmysql.h"

extern DbMySQL db;

ExaminationWidget::ExaminationWidget(QWidget *parent) :
    QWidget(parent),
    examTree(new ExaminationTree(this)),
    examTable(new ExaminationTable(this)) {

    QSplitter *splitter = new QSplitter;
    splitter->addWidget(examTree);
    splitter->addWidget(examTable);
    splitter->setStretchFactor(0, 20);
    splitter->setStretchFactor(1, 80);

    BorderLayout *layout = new BorderLayout;
    layout->addWidget(splitter, BorderLayout::Center);
    this->setLayout(layout);

    QList<QStringList> exams;
    db.getExamInfo(exams);
    if(exams.count() > 0){
        examTable->fillModel(exams);
    }
}

ExaminationWidget::~ExaminationWidget() {
    if(nullptr != examTree)
        delete examTree, examTree = nullptr;

    if(nullptr != examTable)
        delete examTable, examTable = nullptr;
}

void ExaminationWidget::onTreeClicked(const QModelIndex &index) {
    qDebug() << index.row();
}
