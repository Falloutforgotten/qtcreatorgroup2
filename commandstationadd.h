#ifndef COMMANDSTATIONADD_H
#define COMMANDSTATIONADD_H

#include <QUndoCommand>
#include <QGraphicsScene>

/*************************************************************************************/
/***************** Undostack command for adding a station to a scene *****************/
/*************************************************************************************/

class CommandStationAdd : public QUndoCommand
{
public:
  CommandStationAdd( QGraphicsScene* scene, qreal x, qreal y )
    {
      m_station = new Station( x, y );
      m_scene   = scene;
      setText( QString("Station add %1,%2").arg(x).arg(y) );
    }

  ~CommandStationAdd()
    {
      // if station not on scene then delete station
      if ( !m_scene->items().contains( m_station ) )
        delete m_station;
    }

  virtual void undo()    { m_scene->removeItem( m_station ); }

  virtual void redo()    { m_scene->addItem( m_station ); }

private:
  Station*         m_station;    // station being added
  QGraphicsScene*  m_scene;      // scene where station being added
};

#endif  // COMMANDSTATIONADD_H
