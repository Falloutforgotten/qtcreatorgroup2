#include "mainwindow.h"
#include "scene.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QGraphicsView>

/*************************************************************************************/
/*********************** Main application window for QSimulate ***********************/
/*************************************************************************************/

/************************************ constuctor *************************************/

MainWindow::MainWindow() : QMainWindow()
{
  // add drop down menus (currently empty)
  menuBar()->addMenu("&File");
  menuBar()->addMenu("&Edit");
  menuBar()->addMenu("&View");
  menuBar()->addMenu("&Simulate");
  menuBar()->addMenu("&Help");

  // create scene and central widget view of scene
  m_scene               = new Scene();
  QGraphicsView*   view = new QGraphicsView( m_scene );
  view->setAlignment( Qt::AlignLeft | Qt::AlignTop );
  view->setFrameStyle( 0 );
  setCentralWidget( view );

  // connect message signal from scene to showMessage slot
    connect( m_scene, SIGNAL(message(QString)), this, SLOT(showMessage(QString)) );

  // add status bar message
  statusBar()->showMessage("QSimulate has started");


}

/************************************ showMessage ************************************/

void  MainWindow::showMessage( QString msg )
{
  // display message on main window status bar
  statusBar()->showMessage( msg );
}
