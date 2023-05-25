#ifndef DEMO_H
#define DEMO_H

#include "filedownloader.h"
#include "qgraphicsitem.h"
#include <QDialog>

namespace Ui {
class demo;
}

class demo : public QDialog
{
    Q_OBJECT

public:
    explicit demo(QWidget *parent = nullptr);
    ~demo();

private:
    Ui::demo *ui;
    QGraphicsPixmapItem* _pixmap_item;
    FileDownloader *m_pImgCtrl;
    bool eventFilter(QObject* object, QEvent* event) override;
    void zoomedSignalCatch();
    void highVelocitySwipeCatch();

private slots:
    void loadImage();
    void getImage();
};

#endif // DEMO_H
