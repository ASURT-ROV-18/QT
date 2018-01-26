#pragma once

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QWidget>
#include <unordered_map>

#include "modeList.h"
#include <QDebug>

namespace UIW {

class statusBar : public QWidget {
  Q_OBJECT

private:
  QHBoxLayout *stBar;
  QLabel *Js, *RPI, *NetW, *Cycles, *Speed;
  //    UpCombo *mode_list;
  QString modes[5] = {"Normal", "Swordfish", "Return"};
  int i = 0;
  std::unordered_map<std::string, float> _sendData;

public:
  UpCombo *mode_list;
  explicit statusBar(QWidget *parent) {
    this->setParent(parent);
    stBar = new QHBoxLayout(this);
    Js = new QLabel(this);
    RPI = new QLabel(this);
    NetW = new QLabel(this);
    Speed = new QLabel(this);
    mode_list = new UpCombo(this);
    Cycles = new QLabel(this);

    for (i = 0; i < 3; i++) {
      mode_list->addItem(modes[i]);
    }

    stBar->setSpacing(0);
    stBar->setContentsMargins(0, 0, 0, 0);

    Js->setText("Joystick");
    RPI->setText("Tcp");
    NetW->setText("Ethernet");
    Cycles->setText("Cycles: 0.5 ");
    Speed->setText("Speed : 0 %");

    Js->setStyleSheet("QLabel{color : red; font-size: 11px; }");
    RPI->setStyleSheet("QLabel{color : red; font-size: 11px;}");
    NetW->setStyleSheet("QLabel{color : red; font-size: 11px; }");
    Cycles->setStyleSheet("QLabel{color : white; font-size: 11px;}");
    Speed->setStyleSheet("QLabel{color : white; font-size: 11px;}");

    stBar->addWidget(Js, 0, Qt::AlignLeft);
    stBar->addSpacing(10);

    stBar->addWidget(RPI, 0, Qt::AlignLeft);
    stBar->addSpacing(10);

    stBar->addWidget(NetW, 0, Qt::AlignLeft);

    stBar->addStretch();

    stBar->addStretch();

    stBar->addWidget(Speed, 0, Qt::AlignRight);
    stBar->addSpacing(10);

    stBar->addWidget(Cycles, 0, Qt::AlignRight);
    stBar->addSpacing(10);

    stBar->addWidget(mode_list, 0, Qt::AlignRight);

    connect(mode_list, SIGNAL(currentIndexChanged(int)), this,
            SLOT(modeListChanged(int)));
  }
public slots:

  void joystickConnected(bool Connected) {
    if (Connected) {
      Js->setStyleSheet("QLabel{color : white; font-size: 11px; }");
    } else {
      Js->setStyleSheet("QLabel{color : red; font-size: 11px; }");
    }
  }

  void ethernetConnected(bool Connected) {
    if (Connected) {
      NetW->setStyleSheet("QLabel{color : white; font-size: 11px; }");
    } else {
      NetW->setStyleSheet("QLabel{color : red; font-size: 11px; }");
    }
  }

  void RPiConnected(bool Connected) {
    if (Connected) {
      RPI->setStyleSheet("QLabel{color : white; font-size: 11px; }");
    } else {
      RPI->setStyleSheet("QLabel{color : red; font-size: 11px; }");
      mode_list->setCurrentIndex(0);
    }
  }

  void gripCycles(float cycles) {
    Cycles->setText("Cycles : " + QString::number(cycles));
  }

  void speedIndicator(int speed) {
    Speed->setText("Speed : " + QString::number(speed) + " %");
  }

  void modeListChanged(int selectedMode) {
    qDebug() << selectedMode;
    _sendData["currentmode"] = selectedMode;
    emit updateMode(_sendData);
  }

signals:
  void updateMode(std::unordered_map<std::string, float>);
};
}
