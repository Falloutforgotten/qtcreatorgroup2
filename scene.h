#ifndef SCENE_H
#define SCENE_H
class QXmlStreamReader;
#include <QGraphicsScene>
class QGraphicsSceneMouseEvent;
class Station;
/*************************************************************************************/
/******************** Scene representing the simulated landscape *********************/
/*************************************************************************************/
class QXmlStreamWriter;
class QUndoStack;
class QXmlStreamReader;
class Scene : public QGraphicsScene
{
  Q_OBJECT
public slots:
  void  selectStations();                     // records selected stations & positions
signals:
void  message( QString );                                  // info text message signal
protected:
void  mouseReleaseEvent( QGraphicsSceneMouseEvent* );      // receive mouse release events
void  mousePressEvent( QGraphicsSceneMouseEvent* );        // receive mouse press events
void  contextMenuEvent( QGraphicsSceneContextMenuEvent* ); // receive context menu events
public:
   Scene( QUndoStack* );
   void  writeStream( QXmlStreamWriter* );
   void  readStream( QXmlStreamReader* );                     // read scene data from xml stream
private:
  typedef QPair<Station*,QPointF>     StationPos;
  QList<StationPos>   m_stations;             // currently selected stations & start positions
  QUndoStack*  m_undoStack;                 // undo stack for undo & redo of commands

};

#endif  // SCENE_H
