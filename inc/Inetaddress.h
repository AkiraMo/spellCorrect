 ///
 /// @file    Inetaddress.h
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-27 09:35:23
 ///

#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__

#include <string>
#include <netinet/in.h>

class Inetaddress
{
public:
	explicit Inetaddress(uint16_t port);
    Inetaddress(const std::string &ip, uint16_t port);
    Inetaddress(const struct sockaddr_in &add);

    void setSockAddrInet(const struct sockaddr_in &add);
	const struct sockaddr_in *getSockAddrInet() const;

   std::string toIp() const;
   uint16_t toPort() const;

private:
	struct sockaddr_in _add;
};

#endif
