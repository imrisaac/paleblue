#include "imageitem.h"
#include <QDebug>
#include <QPainter>

ImageItem::ImageItem(QQuickItem *parent):QQuickPaintedItem(parent)
{
    qDebug() << Q_FUNC_INFO << "initializing new item, parent is: " << parent;
    setImage(QImage("/resources/10848x10848.jpg"));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(LoadImage()));
    timer->start(60*16*1000);
}

QImage ImageItem::image() const
{
    qDebug() << Q_FUNC_INFO << "image requested...";
    return m_image;
}

void ImageItem::setImage(const QImage &image)
{
    qDebug() << Q_FUNC_INFO << "setting new image...";
    if(image == m_image){
        // image is unchanged but we went through all the trouble to download it so update it anyway
        qDebug() << Q_FUNC_INFO << "image unchanged";
    }
    if(image.isNull()){
        qDebug() << Q_FUNC_INFO << "image null";
    }
    m_image = image;
    emit imageChanged();
    update();
}

const QImage& ImageItem::getImage() const {
    return m_image;
}

void ImageItem::paint(QPainter *painter)
{
    if(m_image.isNull())
        return;
    qDebug() << Q_FUNC_INFO << "paint requested...";

    QRectF bounding_rect = boundingRect();
    QImage scaled = m_image.scaledToHeight(bounding_rect.height());
    QPointF center = bounding_rect.center() - scaled.rect().center();

    if (center.x() < 0)
        center.setX(0);
    if (center.y() < 0)
        center.setY(0);
    painter->drawImage(center, scaled);
}

void ImageItem::updateImage(){
    LoadImage();
}

void ImageItem::LoadImage(){
    qInfo() << "get image from: " << m_image_source;
    m_pImgCtrl = new FileDownloader(m_image_source, this);
    connect(m_pImgCtrl, SIGNAL (downloaded()), this, SLOT (PaintImage()));
}

void ImageItem::PaintImage(){
    QImage image;
    qInfo() << "image downloaded";
    //buttonImage.loadFromData(m_pImgCtrl->downloadedData());
    image.loadFromData(m_pImgCtrl->downloadedData());
    setImage(image);
}

QUrl ImageItem::getSource() const{
    return m_image_source;
}

void ImageItem::setSource(QUrl &source){
    qDebug() << Q_FUNC_INFO << "setting image source: " << source;
    if(m_image_source != source){
        m_image_source = source;
        emit sourceChanged();
    }
}

QUrl ImageItem::getSourceDefault() const{
    return m_image_source;
}

void ImageItem::setSourceDefault(QUrl &source){
}


