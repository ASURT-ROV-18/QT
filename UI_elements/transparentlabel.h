#ifndef TRANSPARENTLABEL_H
#define TRANSPARENTLABEL_H

#include <QString>
#include <QLabel>

class TransparentLabel : public QWidget
{
    Q_OBJECT

private:
    QString fixedText;
    QLabel *label;

public:
    TransparentLabel(QWidget *parent, QString fixedPart = "");
    void setText(QString text);
};

#endif // TRANSPARENTLABEL_H
