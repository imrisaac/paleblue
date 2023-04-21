#include "graphicsviewzoom.h"
#include <QMouseEvent>
#include <QApplication>
#include <QScrollBar>
#include <qmath.h>

Graphics_view_zoom::Graphics_view_zoom(QGraphicsView* view)
    : QWidget(view), _view(view)
{
    _view->viewport()->installEventFilter(this);
    _view->setMouseTracking(true);
    _modifiers = Qt::ControlModifier;
    _zoom_factor_base = 1.0015;
    _start_transform = _view->transform();
}

void Graphics_view_zoom::gentle_zoom(double factor) {
    qInfo() << "setting zoom " << factor;
    if(_view->transform().m11() < 0.00119713 && factor < 1){
        qInfo() << "min zoom reached";
        emit zoomed();
        return;
    }else if (_view->transform().m11() > 5.7449 && factor > 1){
        qInfo() << "max zoom reached";
        emit zoomed();
        return;
    }
    _view->scale(factor, factor);
    qInfo() << "new size " << _view->transform();
    _view->centerOn(target_scene_pos);
    QPointF delta_viewport_pos = target_viewport_pos - QPointF(_view->viewport()->width() / 2.0,
                                                               _view->viewport()->height() / 2.0);
    QPointF viewport_center = _view->mapFromScene(target_scene_pos) - delta_viewport_pos;
    _view->centerOn(_view->mapToScene(viewport_center.toPoint()));
    emit zoomed();
}

void Graphics_view_zoom::set_modifiers(Qt::KeyboardModifiers modifiers) {
    _modifiers = modifiers;
}

void Graphics_view_zoom::set_zoom_factor_base(double value) {
    _zoom_factor_base = value;
}

bool Graphics_view_zoom::eventFilter(QObject *object, QEvent *event) {
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
        QPointF delta = target_viewport_pos - mouse_event->pos();

        if (qAbs(delta.x()) > 5 || qAbs(delta.y()) > 5) {
            target_viewport_pos = mouse_event->pos();
            target_scene_pos = _view->mapToScene(mouse_event->pos());
        }
    } else if (event->type() == QEvent::Wheel) {
        QWheelEvent* wheel_event = static_cast<QWheelEvent*>(event);
        if (QApplication::keyboardModifiers() == _modifiers) {
            //if (wheel_event->orientation() == Qt::Vertical) {
            double angle = wheel_event->angleDelta().y();
            double factor = qPow(_zoom_factor_base, angle);
            gentle_zoom(factor);
            return true;
            //}
        }
    } else if (event->type() == QEvent::MouseButtonRelease){
        QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
        const QPoint movePos { mouse_event->pos() };
        const int begin        = m_swipeVertical ? pressPos.y() : pressPos.x();
        const int end          = m_swipeVertical ? movePos.y()  : movePos.x();
        const int distance     = end - begin;
//        const int minDistance  = minSwipeDistance();
        const int velocity     = m_swipeVertical ? mouse_event->point(mouse_event->pointCount() - 1).velocity().y() : mouse_event->point(mouse_event->pointCount() - 1).velocity().x();
//        const int minVelocity  = swipeVelocity();
//        const int frameWidth   = frameRect().width();
//        const int frameHeight  = frameRect().height();
        qInfo() << "mouse distance: " << distance;
        qInfo() << "mouse velocity: " << velocity;
        if(velocity > 4000){
            qInfo() << "emit high velocity swipe";
            emit highVelocitySwipe();
        }
    } else if (event->type() == QEvent::MouseButtonDblClick) {
        qInfo() << "mouse dbl click event";
        _view->setTransform(_start_transform);
    }
    Q_UNUSED(object)
    return false;
}
