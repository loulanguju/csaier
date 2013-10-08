#include<QApplication>

#include"SaiErMainWindow.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  QSettings *settings = new QSettings("CSaiEr.ini", QSettings::IniFormat);

  SaiErMainWindow *win = new SaiErMainWindow;
  win->show ();

  delete settings;

  return app.exec ();
}
