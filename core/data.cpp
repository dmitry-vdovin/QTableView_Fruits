// core/data.cpp
#include "data.h"
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

void Fruit::load(const QString& fileName) {
    M.clear();
    QFile f(fileName);
    if (!f.open(QIODevice::ReadOnly|QIODevice::Text)) return;
    QTextStream in(&f);
    while (!in.atEnd()) {
        QStringList parts = in.readLine().split(QRegularExpression("\\s+"));
        if (parts.size() < 2) continue;
        S1 item{ parts.at(0), parts.at(1) };
        M.append(item);
    }
}

void Fruit::save(const QString& fileName) const {
    QFile f(fileName);
    if (!f.open(QIODevice::WriteOnly|QIODevice::Text)) return;
    QTextStream out(&f);
    for (auto& item : M)
        out << item.Name << '\t' << item.Section << '\n';
}

void Fruit::merge(const Fruit& a, const Fruit& b) {
    M = a.M;
    for (auto& item : b.M)
        if (!M.contains(item))
            M.append(item);
    // при желании: qSort(M.begin(), M.end(), [](const S1&a,const S1&b){ return a.Name<b.Name; });
}

// Аналогично для Bag:
void Bag::load(const QString& fileName) { /* … */ }
void Bag::save(const QString& fileName) const { /* … */ }
void Bag::merge(const Bag& a, const Bag& b) { /* … */ }
