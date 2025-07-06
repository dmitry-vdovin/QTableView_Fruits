// gui/mainwindow.h
#pragma once
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QTabWidget>
#include "core/data.h"
#include "s1model.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
    // исходные и результирующие контейнеры
    Fruit A1, A2, AResult;

    // модели для трёх таблиц
    S1Model *mS1Src1, *mS1Src2, *mS1Res;
    // виды (таблицы)
    QTableView *viewSrc1, *viewSrc2, *viewRes;
    // кнопки
    QPushButton *btnLoad, *btnMerge, *btnSave;

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onLoad();   // загружает Ob1/Ob2
    void onMerge();  // объединяет A1+A2 → AResult
    void onSave();   // сохраняет Ob.txt
};
