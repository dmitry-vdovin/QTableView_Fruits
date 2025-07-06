// gui/mainwindow.cpp
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QMessageBox>
#include <QFileInfo>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // создаём модели, привязаные к разным контейнерам
    mS1Src1 = new S1Model(&A1, this);
    mS1Src2 = new S1Model(&A2, this);
    mS1Res  = new S1Model(&AResult, this);

    // создаём таблицы
    viewSrc1 = new QTableView; viewSrc1->setModel(mS1Src1);
    viewSrc2 = new QTableView; viewSrc2->setModel(mS1Src2);
    viewRes  = new QTableView; viewRes->setModel(mS1Res);

    // вкладки для трёх таблиц
    QTabWidget *tabs = new QTabWidget;
    tabs->addTab(viewSrc1, "Source 1");
    tabs->addTab(viewSrc2, "Source 2");
    tabs->addTab(viewRes,  "Result");

    // кнопки
    btnLoad  = new QPushButton("Load");
    btnMerge = new QPushButton("Merge");
    btnSave  = new QPushButton("Save");

    // слоты
    connect(btnLoad,  &QPushButton::clicked, this, &MainWindow::onLoad);
    connect(btnMerge, &QPushButton::clicked, this, &MainWindow::onMerge);
    connect(btnSave,  &QPushButton::clicked, this, &MainWindow::onSave);

    // раскладка
    QHBoxLayout *h = new QHBoxLayout;
    h->addWidget(btnLoad);
    h->addWidget(btnMerge);
    h->addWidget(btnSave);

    QVBoxLayout *v = new QVBoxLayout;
    v->addWidget(tabs);
    v->addLayout(h);

    QWidget *w = new QWidget;
    w->setLayout(v);
    setCentralWidget(w);
    resize(800, 600);

    // автозагрузка при старте (опционально)
     onLoad();
}

void MainWindow::onLoad()
{
    // стартуем из папки, где лежит .exe
    QString dir = QCoreApplication::applicationDirPath();

    QString f1 = QFileDialog::getOpenFileName(this, "Open Ob1.txt",
                                              dir, "Text files (*.txt)");
    if (f1.isEmpty()) return;

    QString f2 = QFileDialog::getOpenFileName(this, "Open Ob2.txt",
                                              QFileInfo(f1).absolutePath(),
                                              "Text files (*.txt)");
    if (f2.isEmpty()) return;

    QString f3 = QFileDialog::getOpenFileName(this, "Open TOb1.txt",
                                              QFileInfo(f1).absolutePath(),
                                              "Text files (*.txt)");
    if (f3.isEmpty()) return;

    QString f4 = QFileDialog::getOpenFileName(this, "Open TOb2.txt",
                                              QFileInfo(f1).absolutePath(),
                                              "Text files (*.txt)");
    if (f4.isEmpty()) return;

    /* ===== Загрузка ваших контейнеров ===== */
    A1.load(f1);
    A2.load(f2);
   // B1.load(f3);
   // B2.load(f4);

    /* ===== Обновляем три таблицы ===== */
    mS1Src1->layoutChanged();
    mS1Src2->layoutChanged();
    AResult.M.clear();          // результат обнуляем, ждём Merge
    mS1Res->layoutChanged();

    QMessageBox::information(this, "Loaded",
                             "Файлы успешно загружены:\n"
                                 + f1 + "\n" + f2 + "\n" + f3 + "\n" + f4);
}

void MainWindow::onMerge()
{
    // объединяем
    AResult.merge(A1, A2);
    // показываем результат
    mS1Res->layoutChanged();
}

void MainWindow::onSave()
{
    // сохраняем результат
    AResult.save("Ob.txt");
    QMessageBox::information(this, "Saved", "Result saved to Ob.txt");
}
