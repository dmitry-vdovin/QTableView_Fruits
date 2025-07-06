#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QApplication>

MainWindow::MainWindow(QWidget*)
{
    /* модели на результаты (объединённые списки) */
    mS1Res = new S1Model(&AResult,this);
    mS2Res = new S2Model(&BResult,this);

    viewS1 = new QTableView; viewS1->setModel(mS1Res);
    viewS2 = new QTableView; viewS2->setModel(mS2Res);

    auto tabs = new QTabWidget;
    tabs->addTab(viewS1,"Objects (no qty)");
    tabs->addTab(viewS2,"Objects (with qty)");

    btnLoad  = new QPushButton("Load"),  btnLoad ->setObjectName("btnLoad");
    btnMerge = new QPushButton("Merge"), btnMerge->setObjectName("btnMerge");
    btnSave  = new QPushButton("Save"),  btnSave ->setObjectName("btnSave");

    connect(btnLoad ,&QPushButton::clicked,this,&MainWindow::onLoad);
    connect(btnMerge,&QPushButton::clicked,this,&MainWindow::onMerge);
    connect(btnSave ,&QPushButton::clicked,this,&MainWindow::onSave);

    auto h = new QHBoxLayout; h->addWidget(btnLoad); h->addWidget(btnMerge); h->addWidget(btnSave);
    auto v = new QVBoxLayout; v->addWidget(tabs); v->addLayout(h);

    auto w = new QWidget; w->setLayout(v);
    setCentralWidget(w);
    resize(700,500);
}

/* --- слоты --- */
void MainWindow::onLoad()
{
    A1.load("Ob1.txt");  A2.load("Ob2.txt");
    B1.load("TOb1.txt"); B2.load("TOb2.txt");
    mS1Res->layoutChanged();
    mS2Res->layoutChanged();
}
void MainWindow::onMerge()
{
    AResult.merge(A1,A2);
    BResult.merge(B1,B2);
    mS1Res->layoutChanged();
    mS2Res->layoutChanged();
}
void MainWindow::onSave()
{
    AResult.save("Ob.txt");
    BResult.save("TOb.txt");
}
