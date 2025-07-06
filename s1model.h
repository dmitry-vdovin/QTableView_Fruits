#pragma once
#include <QAbstractTableModel>
#include "core/data.h"

class S1Model : public QAbstractTableModel
{
    Q_OBJECT
    Fruit* src;                  // работаем напрямую с данными
public:
    enum Col { NameCol, SectionCol, ColCount };
    explicit S1Model(Fruit* f, QObject* p=nullptr) : QAbstractTableModel(p), src(f) {}

    int rowCount(const QModelIndex& ={}) const override { return src->M.size(); }
    int columnCount(const QModelIndex& ={}) const override { return ColCount; }

    QVariant headerData(int s, Qt::Orientation o, int r) const override {
        if (r!=Qt::DisplayRole || o!=Qt::Horizontal) return {};
        return s==NameCol ? "Name" : "Section";
    }
    QVariant data(const QModelIndex& i, int r) const override {
        if(!i.isValid() || (r!=Qt::DisplayRole && r!=Qt::EditRole)) return {};
        const auto& v = src->M.at(i.row());
        return i.column()==NameCol ? v.Name : v.Section;
    }
    bool setData(const QModelIndex& i,const QVariant& val,int r) override {
        if(r!=Qt::EditRole||!i.isValid()) return false;
        auto& v = src->M[i.row()];
        (i.column()==NameCol ? v.Name : v.Section)=val.toString();
        emit dataChanged(i,i);
        return true;
    }
    Qt::ItemFlags flags(const QModelIndex& i) const override {
        return QAbstractTableModel::flags(i)|Qt::ItemIsEditable;
    }
};
