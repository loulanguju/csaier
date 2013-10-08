#include <QString>
#include <QByteArray>
#include <QDataStream>
#include <QIODevice>
#include <QUdpSocket>

#include "SaiErDCBANetwork.h"

#define NETWORK_SERVICE "int"
#define NETWORK_PORT 3848

static void packetEncrypt(char *s, int len);
static void packetDecrypt(char *s, int len);

bool SaiErDCBANetwork::install() {
  return true;
}

bool SaiErDCBANetwork::uninstall () {
  return true;
}

/************************************************************
 * bool login() ;
 * 登陆服务器
 ***********************************************************/
bool SaiErDCBANetwork::login() {

  return true;
}

bool SaiErDCBANetwork::innerLogin() {
  QByteArray datagram;
  QDataStream out(&datagram, QIODevice::WriteOnly);

  out.setVersion (QDataStream::Qt_4_8);

  packetEncrypt (datagram.data (), datagram.length ()); // 数据包加密

  return true;
}

bool SaiErDCBANetwork::logout() {
  return true;
}

bool SaiErDCBANetwork::needKeepLinked() {
  return true;
}

bool SaiErDCBANetwork::retry() {
  return true;
}

static void packetEncrypt(char *s, int len) {
  if (s == NULL || len <= 0x0) return ;

  for (int i = 0; i < len; i++) {
      char c, temp, dest;

      c = s[i];
      dest = (c & 0x1) << 7;

      temp = (c & 0x2) >> 1;
      dest = temp | dest;

      temp = (c & 0x4) << 2;
      dest = temp | dest;

      temp = (c & 0x8) << 2;
      dest = temp | dest;

      temp = (c & 0x10) << 2;
      dest = temp | dest;

      temp = (c & 0x20) >> 2;
      dest = temp | dest;

      temp = (c & 0x40) >> 4;
      dest = temp | dest;

      temp = (c & 0x80) >> 6;
      dest = temp | dest;

      s[i] = dest;
    }
  return ;
}

static void packetDecrypt(char *s, int len) {
  if (s == NULL || len <= 0x0) return ;

  for (int i = 0; i < len; i++) {
      char c, temp ,dest;

      c = s[i];

      dest = (c & 0x1) << 1;

      temp = (c & 0x2) << 6;
      dest = temp | dest;

      temp = (c & 0x4) << 4;
      dest = temp | dest;

      temp = (c & 0x8) << 2;
      dest = temp | dest;

      temp = (c & 0x10) >> 2;
      dest = temp | dest;

      temp = (c & 0x20) >> 2;
      dest = temp | dest;

      temp = (c & 0x40) >> 2;
      dest = temp | dest;

      temp = (c & 0x80) >> 7;
      dest = temp | dest;

      s[i] = dest;
   }
}
