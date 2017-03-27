#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include "station.h"
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QUndoStack>
#include "commandstationadd.h"
#include "commandstationmove.h"
#include "commandstationdelete.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

//test

/*************************************************************************************/
/******************** Scene representing the simulated landscape *********************/
/*************************************************************************************/

/************************************ constuctor *************************************/
/************************************ writeStream ************************************/

void  Scene::writeStream( QXmlStreamWriter* stream )
{
  // write station data to xml stream
  foreach( QGraphicsItem*  item, items() )
  {
    Station*  station = dynamic_cast<Station*>( item );
    if ( station )
    {
      stream->writeEmptyElement( "station" );
      stream->writeAttribute( "x", QString("%1").arg(station->x()) );
      stream->writeAttribute( "y", QString("%1").arg(station->y()) );
    }
  }
}
void  Scene::mousePressEvent( QGraphicsSceneMouseEvent* event )
{
  // only interested if left mouse button pressed
  if ( event->button() != Qt::LeftButton ) return;

  // set local variables and check if existing station clicked
  qreal           x = event->scenePos().x();
  qreal           y = event->scenePos().y();
  Station*  station = dynamic_cast<Station*>( itemAt( x, y ) );

  // if station not clicked and right mouse button pressed, create new Station
  if ( station == 0 && event->button() == Qt::LeftButton )
  {
    m_undoStack->push( new CommandStationAdd( this, x, y ) );
    emit message( QString("Station add at %1,%2").arg(x).arg(y) );
  }

  // call base mousePressEvent to handle other mouse press events
  QGraphicsScene::mousePressEvent( event );

  // emit informative message
  emit message( QString("Station add at %1,%2").arg(x).arg(y) );
}
Scene::Scene( QUndoStack* undoStack ) : QGraphicsScene()
{
    // create invisible item to provide default top-left anchor to scene
      addLine( 0, 0, 0, 1, QPen(Qt::transparent, 1) );
      // initialise variables
       m_undoStack     = undoStack;
       // connect selectionChanged signal to selectStations slot
       connect( this, SIGNAL(selectionChanged()), this, SLOT(selectStations()) );

}
/********************************* contextMenuEvent **********************************/

void  Scene::contextMenuEvent( QGraphicsSceneContextMenuEvent* event )
{
  // we only want to display a menu if user clicked a station
  qreal     x       = event->scenePos().x();
  qreal     y       = event->scenePos().y();
  Station*  station = dynamic_cast<Station*>( itemAt( x, y ) );
  if ( station == 0 ) return;

  // display context menu and action accordingly
  QMenu     menu;
  QAction*  deleteAction = menu.addAction("Delete Station");
  if ( menu.exec( event->screenPos() ) == deleteAction )
  {
      m_undoStack->push( new CommandStationDelete( this, station ) );
    emit message( QString("Station deleted at %1,%2").arg(x).arg(y) );
  }
}
/********************************** selectStations ***********************************/

void  Scene::selectStations()
{
  // refresh record of selected stations and their starting positions
  m_stations.clear();
  foreach( QGraphicsItem* item, selectedItems() )
    if ( dynamic_cast<Station*>( item ) )
    m_stations.append( qMakePair( dynamic_cast<Station*>( item ), item->pos() ) );
}
/********************************* mouseReleaseEvent *********************************/

void  Scene::mouseReleaseEvent( QGraphicsSceneMouseEvent* event )
{
  // if any stations moved, then create undo commands
  foreach( StationPos station , m_stations )
    if ( station.first->pos() != station.second )
      m_undoStack->push( new CommandStationMove( station.first,
                             station.second.x(), station.second.y(),
                             station.first->x(), station.first->y() ) );

  // refresh record of selected stations and call base mouseReleaseEvent
  selectStations();
  QGraphicsScene::mouseReleaseEvent( event );
}
/************************************ readStream *************************************/

void  Scene::readStream( QXmlStreamReader* stream )
{
  // read station data from xml stream
  while ( !stream->atEnd() )
  {
    stream->readNext();
    if ( stream->isStartElement() && stream->name() == "station" )
    {
      qreal x = 0.0, y = 0.0;
      foreach( QXmlStreamAttribute attribute, stream->attributes() )
      {
        if ( attribute.name() == "x" ) x = attribute.value().toString().toDouble();
        if ( attribute.name() == "y" ) y = attribute.value().toString().toDouble();
      }
      addItem( new Station( x, y ) );
    }
  }
}
