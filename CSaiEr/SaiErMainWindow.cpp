#include <stdio.h>
#include "SaiErMainWindow.h"

SaiErMainWindow::SaiErMainWindow(QWidget *parent) :
  QMainWindow(parent) {

  this->createActions ();
  this->createMenu ();

  /****** Create logo label */
  logoLabel = new QLabel;
  QImage *image = new QImage("://img/main.png");
  logoLabel->setPixmap (QPixmap::fromImage (*image));

  /****** Create a User Account */
  this->createUserGroupBox ();

  /***** Create Button */
  QHBoxLayout *userButtoonBoxLayout = new QHBoxLayout;
  loginButton = new QPushButton(tr("Log In"));
  connect(loginButton, SIGNAL(clicked()),
          this, SLOT(login()));
  logoutButton = new QPushButton(tr("Log Out"));
  connect(logoutButton, SIGNAL(clicked()),
          this, SLOT(logout()));
  userButtoonBoxLayout->addWidget (loginButton);
  userButtoonBoxLayout->addWidget (logoutButton);

  this->createSaierStatusBar ();

  /****** Create System Tray Icon */
  this->createSystemTrayIcon ();

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget (logoLabel);
  mainLayout->addWidget (userGroupBox);
  mainLayout->addLayout (userButtoonBoxLayout);

  QWidget *widget = new QWidget;
  widget->setLayout (mainLayout);
  this->setCentralWidget (widget);
  this->setWindowTitle (tr("Saier"));
  this->setWindowIcon(QIcon(tr(":/img/Saier.png")));
  this->setFixedSize (Width, Height);


  readSetting ();
  this->online = false; // 初始为不在线
  if (! this->online) this->setStatusTip (tr("Outline"));
  else this->setStatusTip (tr("Online"));
}

SaiErMainWindow::~SaiErMainWindow () {

}

void SaiErMainWindow::closeEvent (QCloseEvent *event) {
  this->writeSetting ();
  printf ("exit\n");
}

void SaiErMainWindow::changeEvent (QEvent *event) {
  if (event->type() == QEvent::WindowStateChange && this->isMinimized ()) {
      QTimer::singleShot (0, this, SLOT(exit()));
    }
}

/*******
 * Slots
 */
void SaiErMainWindow::login () {
  printf("login\n");
  QString name = nameLineEdit->text ();
  QString psw = pswLineEdit->text ();

  printf("name = %s\npsw = %s\n", name.toStdString ().data (), psw.toStdString ().data ());
}

void SaiErMainWindow::logout () {
  printf("logout\n");
  QString name = nameLineEdit->text ();
  QString psw = pswLineEdit->text ();

  printf("name = %s\npsw = %s\n", name.toStdString ().data (), psw.toStdString ().data ());
}

void SaiErMainWindow::exit() {
  this->hide ();
}

void SaiErMainWindow::about () {
  QMessageBox::about (this,
                      tr("About CSaier"),
                      tr("<h2>CSaier 0.1</h2>"
                      "<p>Copyright &copy; 2008 LoulanGuju."
                      "<p>CSaier is a small application that"
                      "demonstrates QAction, QMainWindow, and many other"
                      "Qt classes."));
}

void SaiErMainWindow::trayIconActivated (QSystemTrayIcon::ActivationReason reason) {
  switch (reason) {
    case QSystemTrayIcon::DoubleClick:
      break;
    case QSystemTrayIcon::Trigger:
      this->activateWindow ();
      this->showNormal ();
      this->raise ();
      break;
    case QSystemTrayIcon::MiddleClick:
      break;
    default:
      break;
    }

}

/******
 * Private Methods
 */
void SaiErMainWindow::createActions () {
  /*****
   *Saier Actions
   */
  exitAction = new QAction(tr("&Exit"), this);
  exitAction->setShortcut (tr("Ctrl+Q"));
  exitAction->setStatusTip (tr("Exit the CSaier application."));
  connect (exitAction, SIGNAL(triggered()),
           this, SLOT(close()));


  /******
   * Network Actions
   */
  protocolsAction = new QAction(tr("&Protocols"), this);

  serverAction = new QAction(tr("&Server"), this);
  serverAction->setStatusTip (tr("Setup the server"));


  /*****
   * Help Actions
   */
  docAction = new QAction(tr("&Doc for Saier"), this);
  docAction->setStatusTip (tr("The help documentation of the CSaier"));

  aboutAction = new QAction(tr("About Saier"), this);
  aboutAction->setStatusTip (tr("About the Saier"));
  connect(aboutAction, SIGNAL(triggered()),
          this, SLOT(about()));

  aboutQtAction = new QAction(tr("About Qt"), this);
  aboutQtAction->setStatusTip (tr("About the Qt"));
  connect(aboutQtAction, SIGNAL(triggered()),
          qApp, SLOT(aboutQt()));
}

void SaiErMainWindow::createMenu () {
  /***** Saier Help */
  saierMenu = menuBar ()->addMenu (tr("&Saier"));
  saierMenu->addAction(exitAction);

  /***** Network Menu */
  networkMenu = menuBar ()->addMenu (tr("&Network"));
  networkMenu->addAction(protocolsAction);
  networkMenu->addAction(serverAction);

  /***** Help Menu */
  helpMenu = menuBar ()->addMenu (tr("&Help"));
  helpMenu->setStatusTip (tr("Help"));
  helpMenu->addAction(docAction);
  helpMenu->addSeparator ();
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(aboutQtAction);
}

void SaiErMainWindow::createUserGroupBox () {
  userGroupBox = new QGroupBox(tr("User Account"));

  nameLabel = new QLabel(tr("User Nmae:"));
  nameLineEdit = new QLineEdit;
  nameLineEdit->setStatusTip (tr("Please enter the user's name."));
  nameLineEdit->setMaxLength (30);

  pswLabel = new QLabel(tr("User Password:"));
  pswLineEdit = new QLineEdit;
  pswLineEdit->setStatusTip (tr("Please enter the user's password."));
  pswLineEdit->setEchoMode (QLineEdit::Password);
  pswLineEdit->setMaxLength (30);

  saveUserCheckBox = new QCheckBox(tr("Save User"));
  saveUserCheckBox->setChecked (true);
  autoLinkCheckBox = new QCheckBox(tr("Auto Link"));
  autoLinkCheckBox->setChecked (false);

  QGridLayout *bodyLayout = new QGridLayout();
  bodyLayout->addWidget (nameLabel, 0, 0);
  bodyLayout->addWidget (nameLineEdit, 0, 1, 1, 2);

  bodyLayout->addWidget (pswLabel, 1, 0, 1, 1);
  bodyLayout->addWidget (pswLineEdit, 1, 1, 1, 2);

  bodyLayout->addWidget (saveUserCheckBox, 2, 1);
  bodyLayout->addWidget (autoLinkCheckBox, 2, 2);

  userGroupBox->setLayout (bodyLayout);
}

void SaiErMainWindow::createUserButtons () {

}

void SaiErMainWindow::createSaierStatusBar () {
  statusLabel = new QLabel(tr("Saier"));
  statusLabel->setAlignment (Qt::AlignLeft | Qt::AlignBottom);
  statusBar ()->addWidget (statusLabel);
}

void SaiErMainWindow::createSystemTrayIcon () {
  trayIconMenu = new QMenu(this);

  trayIconMenu->addAction(exitAction);

  trayIcon = new QSystemTrayIcon(this);
  trayIcon->setContextMenu (trayIconMenu);
  trayIcon->setToolTip (tr("Saier"));

  trayIcon->setIcon (QIcon("://img/Saier.png"));
  connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
          this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
  trayIcon->show ();
}

void SaiErMainWindow::writeSetting () {
  QSettings settings("Software Inc.", "CSaiEr");

  settings.beginGroup ("user");
  settings.setProperty ("name", nameLineEdit->text ());
  settings.setProperty ("psw", pswLineEdit->text ());
  settings.endGroup ();

  settings.beginGroup ("system");
  settings.setProperty ("save", saveUserCheckBox->isChecked ());
  settings.setProperty ("autolink", autoLinkCheckBox->isChecked ());
  settings.endGroup ();
}

void SaiErMainWindow::readSetting () {
  QSettings settings("Software Inc.", "CSaiEr");

  settings.beginGroup ("user");
  QString name = settings.value ("name").toString ();
  nameLineEdit->setText (name);
  QString psw = settings.value ("psw").toString ();
  pswLineEdit->setText (psw);
  settings.endGroup ();

  settings.beginGroup ("system");
  bool save = settings.value ("save", true).toBool ();
  saveUserCheckBox->setChecked (save);
  bool autoLink = settings.value ("autolink", false).toBool ();
  autoLinkCheckBox->setChecked (autoLink);
  settings.endGroup ();
}


/*******
 *
 */
bool SaiErMainWindow::onLine () {
  return this->online;
}

SaiErMainWindow* SaiErMainWindow::onLine (bool online) {
  this->online = online;
  return this;
}
