#pragma once
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QTabWidget>
#include "core/data.h"
#include "s1model.h"
#include "s2model.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    /* данные */
    Fruit A1,A2,AResult;
    Bag   B1,B2,BResult;
    /* модели / виды */
    S1Model *mS1Res;
    S2Model *mS2Res;
    QTableView *viewS1, *viewS2;
    /* кнопки */
    QPushButton *btnLoad,*btnMerge,*btnSave;
public:
    MainWindow(QWidget* =nullptr);
private slots:
    void onLoad();   // считываем Ob1/Ob2/TOb1/TOb2
    void onMerge();  // объединяем A1+A2→AResult, B1+B2→BResult
    void onSave();   // сохраняем Ob.txt / TOb.txt
};
