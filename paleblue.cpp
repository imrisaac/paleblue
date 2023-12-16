#include "paleblue.h"
#include "imageitem.h"

PaleBlue::PaleBlue(QQmlApplicationEngine *engine){
    m_east = engine->rootObjects().first()->findChild<QObject*>("image_item_goes_east");
    m_west = engine->rootObjects().first()->findChild<QObject*>("image_item_goes_west");
    m_southeast = engine->rootObjects().first()->findChild<QObject*>("image_item_goes_southeast");

    if (m_east) {
        ImageItem *image_item = qobject_cast<ImageItem*>(m_east);
        image_item->updateImage();
        connect(image_item, SIGNAL(imageChanged()), this, SLOT(GoesEastImageChanged()));
    } else {
        // The instance was not found
        qInfo() << "east object not found";
    }

    if (m_west) {
        ImageItem *image_item = qobject_cast<ImageItem*>(m_west);
        image_item->updateImage();
        connect(image_item, SIGNAL(imageChanged()), this, SLOT(GoesWestImageChanged()));
    } else {
        // The instance was not found
        qInfo() << "west object not found";
    }

}

bool PaleBlue::Init(){
    return true;
}

bool PaleBlue::Run(){
    return true;
}

void PaleBlue::GetImage(QUrl imageUrl, Helper *helper){
}

void PaleBlue::GoesEastImageChanged(){
    qInfo() << "goes east image changed";
}

void PaleBlue::GoesWestImageChanged(){
    qInfo() << "goes west image changed";
}

#include "paleblue.moc"
