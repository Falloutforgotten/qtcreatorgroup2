#ifndef COMMANDSTATIONMOVE_H
#define COMMANDSTATIONMOVE_H

#include "station.h"

#include <QUndoCommand>

/*************************************************************************************/
/***************** Undostack command for moving a station on a scene *****************/
/*************************************************************************************/

class CommandStationMove : public QUndoCommand
{
public:
  CommandStationMove( Station* station, qreal fromX, qreal fromY, qreal toX, qreal toY )
  {
    m_station = station;
    m_from    = QPointF( fromX, fromY );
    m_to      = QPointF( toX, toY );
    setText( QString("Station move %1,%2 -> %3,%4").arg(fromX).arg(fromY).arg(toX).arg(toY) );
  }

  virtual void undo()    { m_station->setPos( m_from ); }

  virtual void redo()    { m_station->setPos( m_to ); }

private:
  Station*   m_station;       // station being moved
  QPointF    m_from;          // original coords
  QPointF    m_to;            // new coords
};

#endif  // COMMANDSTATIONMOVE_H
