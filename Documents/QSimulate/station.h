#ifndef STATION_H
#define STATION_H

#include <QGraphicsItem>

/*************************************************************************************/
/******************* Represents a radio station in the simulation ********************/
/*************************************************************************************/

class Station : public QGraphicsItem
{
public:
  Station( qreal, qreal );                          // constructor

  void     paint( QPainter*,
                  const QStyleOptionGraphicsItem*,
                  QWidget* );                       // implement virtual paint function
  QRectF   boundingRect() const
    { return QRectF(-6.5, -13, 13, 18); }           // implement virtual boundingRect
};

#endif  // STATION_H
