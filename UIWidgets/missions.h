#pragma once

#include <QWidget>

#include "qcontainer.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>
//#include <QHeaderView>
#include <QGridLayout>
#include <QVector>
#include <QFont>

#include <QDebug>

#define STARTING_POINT -1

#define ITEM_Name 0
#define ROOT_Score 1
#define MISSION_Score 1

#define TREE_Height 150

namespace UIW {

class Missions: public QWidget
{
    Q_OBJECT
private:
    QTreeWidget *_Tree;
    QTreeWidgetItem *ChildItem, *ParentItem;

    int topScore = 0;
    int globalScore = 0;
//    int localScore = 0;

    QFont Selected;
    QFont Trivial;

    QContainer *_Box;
    QWidget *_Parent_Widget;
    QGridLayout *_Parent_Grid;

public:
     explicit Missions (QWidget *parent){
        this->setParent(parent);

        _Box = new QContainer(this);
        _Parent_Widget = new QWidget;
        _Parent_Grid = new QGridLayout(_Parent_Widget);

        _Tree = new QTreeWidget (/*this*/_Parent_Widget);
        _Tree->setColumnCount(2);
//        _Tree->header()->setSectionResizeMode(QHeaderView::/*ResizeToContents*/Fixed);
        _Tree->setHeaderHidden(true);
        _Tree->setRootIsDecorated(false);
        _Tree->setStyleSheet("QTreeWidget::indicator{background: rgba(0,0,0,0); border: 1px solid #FFF; margin: 1px} QTreeWidget::indicator:checked { background : rgba(255,255,255,100)}");

        //************************Adding Missions and Sub-Missions with their high scores and scores********************

        ParentItem = AddRoot("Hello", "0/90");
        ChildItem = AddChild(ParentItem, "From the other side","10");
        ChildItem = AddChild(ParentItem, "It's me","50");
        ChildItem = AddChild(ParentItem, "Can you hear me ?","30");

        ParentItem = AddRoot("Hi", "0/100");
        ChildItem = AddChild(ParentItem, "NO!","100");

        ParentItem = AddRoot("Hello2", "0/60");
        ChildItem = AddChild(ParentItem, "From the other side","10");
        ChildItem = AddChild(ParentItem, "It's me","50");

        ParentItem = AddRoot("Hello3", "0/60");
        ChildItem = AddChild(ParentItem, "From the other side","10");
        ChildItem = AddChild(ParentItem, "It's me","50");

        ParentItem = AddRoot("Hello4", "0/60");
        ChildItem = AddChild(ParentItem, "From the other side","10");
        ChildItem = AddChild(ParentItem, "It's me","50");

        //*****************************************************************************************************************

        connect(_Tree,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this , SLOT(on_itemClicked(QTreeWidgetItem*,int)));
        Selected.setBold(true);
        ParentItem = _Tree->topLevelItem(0);
        ChildItem = ParentItem;


        //***********************Resizing _Tree & _Parent_Widget to fit in the qContainer

        _Tree->resizeColumnToContents(1);
        _Tree->setColumnWidth(ITEM_Name, _Tree->sizeHint().width() - (_Tree->columnWidth(1)+30));
        _Tree->setMaximumHeight(TREE_Height);

        _Parent_Grid->addWidget(_Tree,0,0);
        _Parent_Grid->setMargin(0);
        _Parent_Widget->setLayout(_Parent_Grid);

        _Box->setWidget(_Parent_Widget);
        _Box->setTitle("Missions");

        this->setFixedSize(_Box->sizeHint());
    }

    QTreeWidgetItem *AddRoot(QString name, QString score){
        QTreeWidgetItem *itm = new QTreeWidgetItem(_Tree);
        itm->setText(ITEM_Name , name);
        itm->setText(ROOT_Score , score);
        itm->setFlags(Qt::ItemIsUserCheckable);
        itm->setCheckState(ITEM_Name , Qt::Unchecked);
        return itm;
    }

    QTreeWidgetItem *AddChild(QTreeWidgetItem *parent, QString name, QString score){
        QTreeWidgetItem *itm = new QTreeWidgetItem();
        itm->setText(ITEM_Name, name);
        itm->setText(MISSION_Score, score);
        parent->addChild(itm);
        itm->setFlags(itm->flags() | Qt::ItemIsUserCheckable);
        itm->setCheckState(0, Qt::Unchecked);
        topScore += score.toInt();
        return itm;
    }

    void updateScores(int sign){
        QString currentScoreString = ChildItem->text(MISSION_Score);
        int localScore = currentScoreString.toInt();
        globalScore += localScore * sign;
        emit ourCurrentScore(globalScore);
        QString currentParentScoreString = ChildItem->parent()->text(ROOT_Score);
        QString justValueString = currentParentScoreString.left(currentParentScoreString.indexOf("/"));
        currentParentScoreString = currentParentScoreString.remove(0,justValueString.length());
        int localLocalScore = justValueString.toInt();
        localLocalScore += localScore * sign;
        ParentItem->setText(ROOT_Score, QString::number(localLocalScore)+ currentParentScoreString);
    }

    void setHighlighted(QTreeWidgetItem *item){
        //********** To Keep Finished Parent Item Green even after selecting another parent
        if(item->childCount() != 0 ){
            if(item->checkState(ITEM_Name) == Qt::Checked) return;
        }
        //**********************************************************************************
        item->setFont(ITEM_Name , Selected);
        item->setForeground(ITEM_Name,Qt::red);
        item->setFont(MISSION_Score , Selected);
        item->setForeground(MISSION_Score,Qt::red);
    }

    void SetChecked(QTreeWidgetItem *item){
        item->setCheckState(ITEM_Name,Qt::Checked);
    }

    void setUnChecked(QTreeWidgetItem *item){
        item->setCheckState(ITEM_Name,Qt::Unchecked);
    }

    void clearHighlighted(QTreeWidgetItem *item){
        //********** To Keep Finished Parent Item Green even after selecting another parent
        if(item->childCount() != 0 ){
            if(item->checkState(ITEM_Name) == Qt::Checked) return;
        }
        //**********************************************************************************
        item->setFont(ITEM_Name , Trivial);
        item->setForeground(ITEM_Name,Qt::gray);
        item->setFont(MISSION_Score , Trivial);
        item->setForeground(MISSION_Score,Qt::gray);
    }

    int getTopScore(){
        return topScore;
    }

    bool checkRootCompleted(QTreeWidgetItem *item){
        for(int i = 0 ; i < item->childCount() ; i++){
            if(item->child(i)->checkState(ITEM_Name) == Qt::Unchecked) return false;
        }
        return true;
    }

    QTreeWidgetItem *nextChildItem(QTreeWidgetItem *LocalPointer) // to generalize : make it take another parameter (Parent)
    {
        int nextItemIndex = ParentItem->indexOfChild(LocalPointer);
        if(nextItemIndex < ParentItem->childCount()-1){
            nextItemIndex++;
        }else{
            for(int i = 0 ; i < ParentItem->childCount() ; i++){
                if(ParentItem->child(i)->checkState(ITEM_Name) == Qt::Unchecked){
                    nextItemIndex = i;
                    break;
                }
            }
        }
        return ParentItem->child(nextItemIndex);
    }

public slots:

    void on_itemClicked(QTreeWidgetItem *item, int column){
        if(item->childCount() != 0){
            if(ParentItem == item){
                if(!ParentItem->isExpanded()){
                    ParentItem->setExpanded(true);
                    ChildItem = nextChildItem(ParentItem->child(ParentItem->childCount()-1));
                    setHighlighted(ParentItem);
                    setHighlighted(ChildItem);
                }else{
                    clearHighlighted(ChildItem);
                    clearHighlighted(ParentItem);
                    ParentItem->setExpanded(false);
                }
            }else{
                clearHighlighted(ChildItem);
                clearHighlighted(ParentItem);
                ParentItem->setExpanded(false);
                ParentItem = item;
                ParentItem->setExpanded(true);
                ChildItem = nextChildItem(ParentItem->child(ParentItem->childCount()-1));
                setHighlighted(ParentItem);
                setHighlighted(ChildItem);
            }
        }
        else if(item->childCount() == 0){
            if(ChildItem == item && ParentItem == item->parent()){
                if(ChildItem->checkState(ITEM_Name) == Qt::Unchecked){
                    SetChecked(ChildItem);
                    updateScores(1);
                    clearHighlighted(ChildItem);
                    if(checkRootCompleted(ParentItem)){                        
                        clearHighlighted(ParentItem);
                        SetChecked(ParentItem);
                        ParentItem->setExpanded(false);
                        //**********Set ParentItem to green after finished (will return after another parent is selected)
                        ParentItem->setForeground(ITEM_Name,Qt::green);
                        ParentItem->setForeground(MISSION_Score,Qt::green);
                        //*******************************************************
                    }else{
                        ChildItem = nextChildItem(ChildItem);
                        setHighlighted(ChildItem);
                    }
                }else{
                    setUnChecked(ChildItem);
                    if(ParentItem->checkState(ITEM_Name) == Qt::Checked){
                        setUnChecked(ParentItem);
                        setHighlighted(ParentItem); // To return Parent from green to red when submission is unChecked
                    }
                    updateScores(-1);
                }
            }
            else if (ChildItem != item && ParentItem == item->parent()){
                clearHighlighted(ChildItem);
                ChildItem = item;
                setHighlighted(ChildItem);
            }
            else{
                clearHighlighted(ChildItem);
                clearHighlighted(ParentItem);
                ParentItem->setExpanded(false);
                ChildItem = item;
                ParentItem = item->parent();
                setHighlighted(ChildItem);
                setHighlighted(ParentItem);
            }
        }
        emit returnFocus();
    }

signals:
    void ourCurrentScore(float);
    void returnFocus();
};
}
