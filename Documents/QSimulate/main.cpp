#include "mainwindow.h"

#include <QApplication>

//Christian Smith
//Group 2
//Group Members: Marcos Regalado, Zachariah Rodriguez, Luis Berber, and Zac

int main(int argc, char *argv[])
{
  // create main event loop handler and parse command line arguments
  QApplication app(argc, argv);

  // create application main window & enter main event loop
  MainWindow window;
  window.show();
  return app.exec();
}
