#include "mainwindow.h"
#include "scene.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QGraphicsView>
#include <QUndoStack>
#include <QUndoView>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QDateTime>
#include <QXmlStreamReader>

/*************************************************************************************/
/*********************** Main application window for QSimulate ***********************/
/*************************************************************************************/

/************************************ constuctor *************************************/


MainWindow::MainWindow() : QMainWindow()
{

  // add drop down menus (currently empty)
    // add drop down menus
    QMenu*  fileMenu = menuBar()->addMenu( "&File" );
    // create file menu options
    QAction* openAction    = fileMenu->addAction( "&Open ...",         this, SLOT(fileOpen()) );
      openAction->setShortcut( QKeySequence::Open );
    QAction* saveAction    = fileMenu->addAction( "&Save As...",       this, SLOT(fileSaveAs()) );
    saveAction->setShortcut( QKeySequence::Save );
    QMenu*  editMenu = menuBar()->addMenu( "&Edit" );
     QMenu*  viewMenu = menuBar()->addMenu( "&View" );
     menuBar()->addMenu( "&Simulate" );
     menuBar()->addMenu( "&Help" );

     // create undo stack and associated menu actions
     m_undoStack = new QUndoStack( this );
     m_undoView  = 0;
     viewMenu->addAction( "Undo stack", this, SLOT(showUndoStack()) );
     QAction* undoAction = m_undoStack->createUndoAction( this );
     QAction* redoAction = m_undoStack->createRedoAction( this );
     undoAction->setShortcut( QKeySequence::Undo );
     redoAction->setShortcut( QKeySequence::Redo );
     editMenu->addAction( undoAction );
     editMenu->addAction( redoAction );
  // add status bar message
  statusBar()->showMessage("QSimulate has started");
  // create scene and central widget view of scene
  m_scene               = new Scene( m_undoStack );
  QGraphicsView*   view = new QGraphicsView( m_scene );
  view->setAlignment( Qt::AlignLeft | Qt::AlignTop );
  view->setFrameStyle( 0 );
  setCentralWidget( view );
  // connect message signal from scene to showMessage slot
    connect( m_scene, SIGNAL(message(QString)), this, SLOT(showMessage(QString)) );

}
void  MainWindow::showMessage( QString msg )
{
  // display message on main window status bar
  statusBar()->showMessage( msg );
}
void  MainWindow::showUndoStack()
{
  // open up undo stack window
  if ( m_undoView == 0 )
  {
    m_undoView = new QUndoView( m_undoStack );
    m_undoView->setWindowTitle( "QSimulate - Undo stack" );
    m_undoView->setAttribute( Qt::WA_QuitOnClose, false );
  }
  m_undoView->show();
}
/************************************ fileSaveAs *************************************/

bool  MainWindow::fileSaveAs()
{
  // get user to select filename and location
  QString filename = QFileDialog::getSaveFileName();
  if ( filename.isEmpty() ) return false;

  // open the file and check we can write to it
  QFile file( filename );
  if ( !file.open( QIODevice::WriteOnly ) )
  {
    showMessage( QString("Failed to write to '%1'").arg(filename) );
    return false;
  }

  // open an xml stream writer and write simulation data
  QXmlStreamWriter  stream( &file );
  stream.setAutoFormatting( true );
  stream.writeStartDocument();
  stream.writeStartElement( "qsimulate" );
  stream.writeAttribute( "version", "2009-05" );
  stream.writeAttribute( "user", QString(getenv("USERNAME")) );
  stream.writeAttribute( "when", QDateTime::currentDateTime().toString(Qt::ISODate) );
  m_scene->writeStream( &stream );
  stream.writeEndDocument();

  // close the file and display useful message
  file.close();
  showMessage( QString("Saved to '%1'").arg(filename) );
  return true;
}
/************************************* fileOpen **************************************/

bool  MainWindow::fileOpen()
{
  // get user to select filename and location
  QString filename = QFileDialog::getOpenFileName();
  if ( filename.isEmpty() ) return false;

  // open the file and check we can read from it
  QFile file( filename );
  if ( !file.open( QIODevice::ReadOnly ) )
  {
    showMessage( QString("Failed to open '%1'").arg(filename) );
    return false;
  }

  // open an xml stream reader and load simulation data
  QXmlStreamReader  stream( &file );
  Scene*            newScene = new Scene( m_undoStack );
  while ( !stream.atEnd() )
  {
    stream.readNext();
    if ( stream.isStartElement() )
    {
      if ( stream.name() == "qsimulate" )
        newScene->readStream( &stream );
      else
        stream.raiseError( QString("Unrecognised element '%1'").arg(stream.name().toString()) );
    }
  }

  // check if error occured
  if ( stream.hasError() )
  {
    file.close();
    showMessage( QString("Failed to load '%1' (%2)").arg(filename).arg(stream.errorString()) );
    delete newScene;
    return false;
  }

  // close file, display new scene, delete old scene, and display useful message
  file.close();
  m_undoStack->clear();
  QGraphicsView*   view = dynamic_cast<QGraphicsView*>( centralWidget() );
  view->setScene( newScene );
  delete m_scene;
  m_scene = newScene;
  showMessage( QString("Loaded '%1'").arg(filename) );
  return true;
}
