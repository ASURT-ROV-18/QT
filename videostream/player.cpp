/*
    Copyright (C) 2010 Marco Ballesio <gibrovacco@gmail.com>
    Copyright (C) 2011 Collabora Ltd.
      @author George Kiagiadakis <george.kiagiadakis@collabora.co.uk>
    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.
    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "player.h"
#include <QDir>
#include <QUrl>
#include <QGlib/Connect>
#include <QGlib/Error>
#include <QGst/Pipeline>
#include <QGst/ElementFactory>
#include <QGst/Bus>
#include <QGst/Message>
#include <QGst/Query>
#include <QGst/ClockTime>
#include <QGst/Event>
#include <QGst/StreamVolume>

Player::Player(QWidget *parent)
    : QGst::Ui::VideoWidget(parent){
    Player::init();
}

Player::~Player()
{
    if (m_pipeline) {
        m_pipeline->setState(QGst::StateNull);
        stopPipelineWatch();
    }
}

void Player::init()
{
    if (!m_pipeline) {
        m_pipeline =   QGst::Pipeline::create();
        QGst::ElementPtr videosrc;
        try {
            videosrc = QGst::Bin::fromDescription(
                        "udpsrc port=8081 ! application/x-rtp,encoding-name=JPEG,payload=26 ! rtpjpegdepay ! jpegdec !  xvimagesink sync=false"
                        );
        } catch (const QGlib::Error & error) {
            qCritical() << error;
            qFatal("One ore more required elements are missing. Aborting...");
        }
        m_pipeline->add(videosrc);
        if (m_pipeline) {
            //let the video widget watch the pipeline for new video sinks
            watchPipeline(m_pipeline);
            //watch the bus for messages
            QGst::BusPtr bus = m_pipeline->bus();
            bus->addSignalWatch();
//            qCritical() << "Testinggg";
            QGlib::connect(bus, "message", this, &Player::onBusMessage);
        } else {
            qCritical() << "Failed to create the pipeline. Retrying..";
        }
    }
}

QGst::State Player::state() const{
    return m_pipeline ? m_pipeline->currentState() : QGst::StateNull;
}

bool Player::play(){
    if (m_pipeline) {
        m_pipeline->setState(QGst::StatePlaying);
        return 1;
    }else{
        return 0;
    }
}
void Player::onBusMessage(const QGst::MessagePtr & message)
{
    switch (message->type()) {
    case QGst::MessageEos: //End of stream. We reached the end of the file.
        qCritical()<<"eos";
        Q_EMIT stoppedStreaming();
        break;
    case QGst::MessageError: //Some error occurred.
        qCritical() << message.staticCast<QGst::ErrorMessage>()->error();
        qCritical() << "stopped";
        break;
    case QGst::MessageStateChanged: //The element in message->source() has changed state
        if (message->source() == m_pipeline) {
            qCritical()<<"changed";
//            Player::play();
        }
        break;
    default:
        break;
    }
}
#include "moc_player.cpp"
