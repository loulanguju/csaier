#ifndef SAIERDCBANETWORK_H
#define SAIERDCBANETWORK_H

#include "SaiErNetwork.h"

class QString;
class QUdpSocket;

class SaiErDCBANetwork : public SaiErNetwork
{
public:
  bool install();
  bool uninstall ();
  bool login();
  bool logout();
  bool needKeepLinked();
  bool retry();

private:
  bool innerLogin();

private:
  QString username;
  QString userpsw;
  QString macAdress;
  QString ipAdress;

  QUdpSocket *udpSocket; // udp socket
};

#endif // SAIERDCBANETWORK_H
