
#include "scene.h"
#include "station.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QAction>

/*************************************************************************************/
/******************** Scene representing the simulated landscape *********************/
/*************************************************************************************/

/************************************ constuctor *************************************/

Scene::Scene() : QGraphicsScene()
{
  // create invisible item to provide default top-left anchor to scene
  addLine( 0, 0, 0, 1, QPen(Qt::transparent, 1) );
}

/********************************** mousePressEvent **********************************/

void  Scene::mousePressEvent( QGraphicsSceneMouseEvent* event )
{
  // set local variables and check if existing station clicked
  qreal           x = event->scenePos().x();
  qreal           y = event->scenePos().y();
  Station*  station = dynamic_cast<Station*>( itemAt( x, y, QTransform()));

  // if station not clicked and right mouse button pressed, create new Station
  if ( station == 0 && event->button() == Qt::LeftButton )
  {
    addItem( new Station( x, y ) );
    emit message( QString("Station add at %1,%2").arg(x).arg(y) );
  }

  // call base mousePressEvent to handle other mouse press events
  QGraphicsScene::mousePressEvent( event );
}

/********************************* contextMenuEvent **********************************/

void  Scene::contextMenuEvent( QGraphicsSceneContextMenuEvent* event )
{
  // we only want to display a menu if user clicked a station
  qreal     x       = event->scenePos().x();
  qreal     y       = event->scenePos().y();
  Station*  station = dynamic_cast<Station*>( itemAt( x, y, QTransform()) );
  if ( station == 0 ) return;

  // display context menu and action accordingly
  QMenu     menu;
  QAction*  deleteAction = menu.addAction("Delete Station");
  if ( menu.exec( event->screenPos() ) == deleteAction )
  {
    removeItem( station );
    delete station;
    emit message( QString("Station deleted at %1,%2").arg(x).arg(y) );
  }
}
