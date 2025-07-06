#pragma once
#include <QAbstractTableModel>
#include "core/data.h"

class S2Model : public QAbstractTableModel
{
    Q_OBJECT
    Bag* src;
public:
    enum Col { NameCol, NumCol, SectionCol, ColCount };
    explicit S2Model(Bag* b,QObject* p=nullptr):QAbstractTableModel(p),src(b){}

    int rowCount(const QModelIndex& ={}) const override {return src->M.size();}
    int columnCount(const QModelIndex& ={}) const override {return ColCount;}

    QVariant headerData(int s,Qt::Orientation o,int r) const override{
        if(r!=Qt::DisplayRole||o!=Qt::Horizontal) return {};
        return QStringList{"Name","Quantity","Section"}.at(s);
    }
    QVariant data(const QModelIndex& i,int r) const override{
        if(!i.isValid()||(r!=Qt::DisplayRole&&r!=Qt::EditRole)) return {};
        const auto& v=src->M.at(i.row());
        switch(i.column()){
        case NameCol: return v.Name;
        case NumCol:  return v.Num;
        case SectionCol: return v.Section;
        }
        return {};
    }
    bool setData(const QModelIndex& i,const QVariant& val,int r) override{
        if(r!=Qt::EditRole||!i.isValid()) return false;
        auto& v=src->M[i.row()];
        switch(i.column()){
        case NameCol: v.Name=val.toString(); break;
        case NumCol:  v.Num=val.toInt();     break;
        case SectionCol: v.Section=val.toString(); break;
        }
        emit dataChanged(i,i);
        return true;
    }
    Qt::ItemFlags flags(const QModelIndex& i) const override{
        return QAbstractTableModel::flags(i)|Qt::ItemIsEditable;
    }
};
