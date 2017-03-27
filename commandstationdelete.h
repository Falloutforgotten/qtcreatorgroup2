#ifndef COMMANDSTATIONDELETE_H
#define COMMANDSTATIONDELETE_H

#include <QUndoCommand>
#include <QGraphicsScene>

/*************************************************************************************/
/*************** Undostack command for deleting a station from a scene ***************/
/*************************************************************************************/

class CommandStationDelete : public QUndoCommand
{
public:
  CommandStationDelete( QGraphicsScene* scene, Station* station )
  {
    m_scene   = scene;
    m_station = station;
    setText( QString("Station delete %1,%2").arg(station->x()).arg(station->y()) );
  }

  virtual void undo()    { m_scene->addItem( m_station ); }

  virtual void redo()    { m_scene->removeItem( m_station ); }

private:
  QGraphicsScene*  m_scene;      // scene where station being deleted
  Station*         m_station;    // station being deleted
};

#endif  // COMMANDSTATIONDELETE_H
