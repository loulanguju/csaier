#ifndef SAIERNETWORK_H
#define SAIERNETWORK_H

class SaiErNetwork
{
public:
  /*****
   * install and uninstall the module
   */
  virtual bool install() = 0;

  virtual bool uninstall () = 0;

  /******
   * login the server
   */
  virtual bool login() = 0;

  /******
   * logout the server
   */
  virtual bool logout() = 0;

  /*****
   * need keep linked
   */
  virtual bool needKeepLinked() = 0;

  /*****
   * keep linked
   */
  virtual bool retry() = 0;
};

#endif // SAIERNETWORK_H
