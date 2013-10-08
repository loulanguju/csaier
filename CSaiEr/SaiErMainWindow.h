#ifndef SAIERMAINWINDOW_H
#define SAIERMAINWINDOW_H
#include <QtGui>

class SaiErMainWindow : public QMainWindow
{
  Q_OBJECT

public:
   SaiErMainWindow(QWidget *parent = 0);
   ~SaiErMainWindow();

protected:
   void closeEvent(QCloseEvent *event);
   void changeEvent (QEvent * event);

private:
   void createActions();
   void createMenu();
   void createUserGroupBox();
   void createUserButtons();
   void createSaierStatusBar();
   void createSystemTrayIcon();

   void writeSetting();
   void readSetting();

signals:

public slots:
   void login();
   void logout();

   void exit();
   void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
   void about();

private:
   static const int Width = 300;
   static const int Height = 400;

   QMenu *saierMenu;
   QAction *exitAction;

   QMenu *networkMenu;
   QAction *serverAction;
   QAction *protocolsAction;

   QMenu *helpMenu;
   QAction *docAction;
   QAction *aboutAction;
   QAction *aboutQtAction;

   QLabel *logoLabel;

   QGroupBox *userGroupBox;
   QLabel *nameLabel;
   QLineEdit *nameLineEdit;
   QLabel *pswLabel;
   QLineEdit *pswLineEdit;
   QCheckBox *saveUserCheckBox;
   QCheckBox *autoLinkCheckBox;

   QPushButton *loginButton;
   QPushButton *logoutButton;

   QLabel *statusLabel;

   QSystemTrayIcon *trayIcon;
   QMenu *trayIconMenu;

private:
   QSettings settings;
   bool online;

public:
   bool onLine();
   SaiErMainWindow* onLine(bool online);
};

#endif // SAIERMAINWINDOW_H
