#pragma once

#include <QObject>
#include <QWidget>
#include <QComboBox>


namespace UIW
{
class UpCombo : public QComboBox
{
    Q_OBJECT
private:
    int initial_pos;
public:
    explicit UpCombo(QWidget *parent = 0) : QComboBox(parent)
    {
        this->setParent(parent);
        initial_pos = -1;
        this->setFocusPolicy(Qt::FocusPolicy::NoFocus);  // Not Sure whether to use (NoFocus) or (TabFocus)

        //*******Setting ComboBox Style********************
        this->parentWidget()->setStyleSheet("background : rgba(0,0,0,0); color : rgb(255,255,255) ; selection-background-color: rgb(0,0,100)");
    }

    void showPopup()
    {

        QComboBox::showPopup();
        QWidget *popup = this->findChild<QFrame*>();
        popup->setStyleSheet("background : rgba(0,0,0,0) ; color : rgb(255,255,255)");
        initial_pos = initial_pos == -1 ? popup->y() : initial_pos;
        popup->move(popup->x(), initial_pos - this->height() - popup->height());
        popup->update();
        update();
    }

};

}
