// gui/s1model.h
#pragma once
#include <QAbstractTableModel>
#include "core/data.h"

class S1Model : public QAbstractTableModel {
    Q_OBJECT
    Fruit* src;
public:
    enum Col { NameCol, SectionCol, ColCount };
    explicit S1Model(Fruit* f, QObject* p=nullptr)
        : QAbstractTableModel(p), src(f) {}

    int rowCount(const QModelIndex&) const override { return src->M.size(); }
    int columnCount(const QModelIndex&) const override { return ColCount; }

    QVariant headerData(int s, Qt::Orientation o, int role) const override {
        if (role!=Qt::DisplayRole || o!=Qt::Horizontal) return {};
        return s==NameCol ? "Name" : "Section";
    }
    QVariant data(const QModelIndex& idx, int role) const override {
        if (!idx.isValid() || (role!=Qt::DisplayRole && role!=Qt::EditRole)) return {};
        auto &item = src->M.at(idx.row());
        return idx.column()==NameCol ? item.Name : item.Section;
    }
    bool setData(const QModelIndex& idx, const QVariant& v, int role) override {
        if (role!=Qt::EditRole || !idx.isValid()) return false;
        auto &item = src->M[idx.row()];
        if (idx.column()==NameCol) item.Name = v.toString();
        else                     item.Section = v.toString();
        emit dataChanged(idx, idx);
        return true;
    }
    Qt::ItemFlags flags(const QModelIndex& idx) const override {
        return QAbstractTableModel::flags(idx) | Qt::ItemIsEditable;
    }
};
