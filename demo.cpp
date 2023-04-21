#include "demo.h"
#include "ui_demo.h"
#include "graphicsviewzoom.h"

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


  //QGraphicsView view = ui->graphicsView;
  view->setRenderHint(QPainter::Antialiasing);
  QImage image("/home/ireed/Downloads/20230801750_GOES16-ABI-FD-GEOCOLOR-10848x10848.jpg");
  QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
  scene->addItem(item);

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

demo::~demo()
{
  delete ui;
}
