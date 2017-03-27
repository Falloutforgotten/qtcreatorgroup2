#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

/*************************************************************************************/
/*********************** Main application window for QSimulate ***********************/
/*************************************************************************************/
void showUndoStack();               // open up new undo stack window

class QUndoStack;
class QUndoView;
class Scene;

class MainWindow : public QMainWindow
{
Q_OBJECT
public slots:
  void showMessage( QString );        // show message on status bar
  void showUndoStack();
  bool fileSaveAs();                  // save simulation to file returning true if successful
  bool fileOpen();
   // open up new undo stack window
public:
  MainWindow();                       // constructor
private:
  Scene*       m_scene;               // scene representing the simulated landscape
  QUndoStack*  m_undoStack;           // undo stack for undo & redo of commands
  QUndoView*   m_undoView;            // undo stack window to view undo & redo commands

};

#endif  // MAINWINDOW_H
