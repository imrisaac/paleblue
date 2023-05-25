#include "demo.h"
#include "ui_demo.h"
#include "graphicsviewzoom.h"
#include "filedownloader.h"

demo::demo(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::demo)
{
  ui->setupUi(this);
  ui->stackedWidget->animationSpeed(650);

  QGraphicsScene *scene = new QGraphicsScene;
  QImageReader::setAllocationLimit(500);
  // scene.setSceneRect(0, 0, 600, 600);
  scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  scene->setBackgroundBrush(Qt::black);

  QGraphicsView *view = ui->graphicsView_p6;

  getImage();

  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(getImage()));
  timer->start(60*15*1000);


  //QGraphicsView view = ui->graphicsView;
  view->setRenderHint(QPainter::Antialiasing);
  QImage image("/home/ireed/Downloads/20230801750_GOES16-ABI-FD-GEOCOLOR-10848x10848.jpg");
  _pixmap_item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
  scene->addItem(_pixmap_item);

  view->setCacheMode(QGraphicsView::CacheBackground);
  view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
  view->setDragMode(QGraphicsView::ScrollHandDrag);
  view->setScene(scene);
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->fitInView(0, 0, image.width(), image.height(), Qt::KeepAspectRatio);

  Graphics_view_zoom* z = new Graphics_view_zoom(view);
  z->set_modifiers(Qt::NoModifier);

  z->installEventFilter(this);

  connect(z, SIGNAL(zoomed()), z, SLOT(zoomedSignalCatch()));
  connect(z, SIGNAL(highVelocitySwipe()), z, SLOT(highVelocitySwipeCatch()));

  connect(ui->prev,&QAbstractButton::clicked,[this]{
      if(ui->stackedWidget->gotoPrevPage()){
        ui->prev->setEnabled(false);
        ui->next->setEnabled(false);
      }
    });
  connect(ui->next,&QAbstractButton::clicked,[this]{
      if(ui->stackedWidget->gotoNextPage()){
        ui->prev->setEnabled(false);
        ui->next->setEnabled(false);
      }
    });
  connect(ui->stackedWidget,&QSwipeView::animationFinished,[this]{
      ui->prev->setEnabled(true);
      ui->next->setEnabled(true);
    });

}

void demo::zoomedSignalCatch(){
  qInfo() << "caught zoomed";
}

void demo::highVelocitySwipeCatch(){
   qInfo() << "caught high velocity swipe";
}

bool demo::eventFilter(QObject *object, QEvent *event) {
  qInfo() << "event type: " <<   event->type();
}

void demo::getImage(){
  // GOES West
  //QUrl imageUrl("https://cdn.star.nesdis.noaa.gov/GOES18/ABI/FD/GEOCOLOR/10848x10848.jpg");

  // GOES East
  QUrl imageUrl("https://cdn.star.nesdis.noaa.gov/GOES16/ABI/FD/GEOCOLOR/10848x10848.jpg");
  m_pImgCtrl = new FileDownloader(imageUrl, this);
  connect(m_pImgCtrl, SIGNAL (downloaded()), this, SLOT (loadImage()));
  qInfo() << "get image";
}

void demo::loadImage(){
  QImage image;
  qInfo() << "image downloaded";
  //buttonImage.loadFromData(m_pImgCtrl->downloadedData());
  image.loadFromData(m_pImgCtrl->downloadedData());
  _pixmap_item->setPixmap(QPixmap::fromImage(image));
}

demo::~demo()
{
  delete ui;
}
