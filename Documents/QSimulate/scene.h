#ifndef SCENE_H
#define SCENE_H

class QGraphicsSceneMouseEvent;

#include <QGraphicsScene>

/*************************************************************************************/
/******************** Scene representing the simulated landscape *********************/
/*************************************************************************************/

class Scene : public QGraphicsScene
{
  Q_OBJECT
public:
  Scene();                                      // constructor

signals:
  void  message( QString );                                  // info text message signal

protected:
  void  mousePressEvent( QGraphicsSceneMouseEvent* );        // receive mouse press events
  void  contextMenuEvent( QGraphicsSceneContextMenuEvent* ); // receive context menu events
};

#endif  // SCENE_H
