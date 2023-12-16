#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QImage>
#include <QQuickPaintedItem>
#include <QtCore/QUrl>
#include <QTime>
#include <QTimer>

#include "filedownloader.h"

class ImageItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(QUrl source READ getSource WRITE setSource NOTIFY sourceChanged FINAL)
    Q_PROPERTY(QUrl sourceDefault READ getSourceDefault WRITE setSourceDefault NOTIFY sourceChangedDefault FINAL)

public:
    ImageItem(QQuickItem *parent = nullptr);
    QImage image() const;
    void setImage(const QImage &image);
    const QImage& getImage() const;

    void paint(QPainter *painter);
    QUrl getSource() const;
    void setSource(QUrl &source);

    QUrl getSourceDefault() const;
    void setSourceDefault(QUrl &source);

    void updateImage();

signals:
    void imageChanged();
    void sourceChanged();
    void sourceChangedDefault();

private:

    QImage m_image;
    QUrl m_image_source;
    FileDownloader *m_pImgCtrl;

private slots:
    void PaintImage();
    void LoadImage();
};
#endif // IMAGEITEM_H
