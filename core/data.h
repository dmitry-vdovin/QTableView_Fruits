#pragma once
#include <QString>
#include <QVector>
#include <QTextStream>

/* ---------- исходные структуры ---------- */
struct S1 { QString Name; QString Section; bool operator==(const S1& r) const { return Name == r.Name; } };
struct S2 { QString Name; int Num; QString Section; bool operator==(const S2& r) const { return Name == r.Name; } };

/* ---------- контейнеры ---------- */
struct Fruit                     // раньше назывался Ob-или ABS_COMP-вариант без количества
{
    QVector<S1> M;
    void load(const QString& file);          // читает Ob*.txt
    void save(const QString& file) const;    // пишет Ob.txt
    void merge(const Fruit& a, const Fruit& b);
};

struct Bag                       // вариант с количеством (TOb*.txt)
{
    QVector<S2> M;
    void load(const QString& file);
    void save(const QString& file) const;
    void merge(const Bag& a, const Bag& b);
};
