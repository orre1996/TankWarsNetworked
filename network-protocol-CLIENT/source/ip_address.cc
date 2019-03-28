// ip_address.cc
#include "stdafx.h"
#include "types.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

static sockaddr_in
translate(const ip_address &addr)
{
   sockaddr_in result = {};

   result.sin_family = AF_INET;
   result.sin_addr.s_addr = htonl(addr.host_);
   result.sin_port = htons(addr.port_);

   return result;
}

int ip_address::local_addresses(int count, ip_address *addresses)
{
   DWORD size = 0;
   GetAdaptersAddresses(AF_INET,
      GAA_FLAG_INCLUDE_PREFIX,
      NULL,
      NULL,
      &size);

   IP_ADAPTER_ADDRESSES *adapter_addresses = (IP_ADAPTER_ADDRESSES *)calloc(1, size);
   GetAdaptersAddresses(AF_INET,
      GAA_FLAG_INCLUDE_PREFIX,
      NULL,
      adapter_addresses,
      &size);

   int valid_address_count = 0;
   for (IP_ADAPTER_ADDRESSES *iter = adapter_addresses;
      iter != NULL;
      iter = iter->Next)
   {
      if (iter->OperStatus == IfOperStatusUp &&
      (iter->IfType == IF_TYPE_ETHERNET_CSMACD || iter->IfType == IF_TYPE_IEEE80211))
      {
         for (IP_ADAPTER_UNICAST_ADDRESS *ua = iter->FirstUnicastAddress;
            ua != NULL;
            ua = ua->Next)
         {
            char address[1024] = {};
            getnameinfo(ua->Address.lpSockaddr, ua->Address.iSockaddrLength, address, sizeof(address), NULL, 0, NI_NUMERICHOST);
            if (ua->Address.lpSockaddr->sa_family == AF_INET)
            {
               sockaddr_in ai = *(sockaddr_in *)ua->Address.lpSockaddr;
               addresses[valid_address_count].host_ = ntohl(ai.sin_addr.s_addr);
               addresses[valid_address_count].port_ = ntohs(ai.sin_port);

               valid_address_count++;
               if (valid_address_count == count)
               break;
            }
         }
      }
   }

  free(adapter_addresses);

  return valid_address_count;
}

int ip_address::lookup(const char *dns, int count, ip_address *addresses)
{
   ADDRINFO *query_result = NULL;
   ADDRINFO hint = {};
   hint.ai_family = AF_INET;
   hint.ai_socktype = SOCK_DGRAM;

   int valid_addr_count = 0;
   bool result = getaddrinfo(dns, NULL, &hint, &query_result) == 0;
   if (result)
   {
      ADDRINFO *iter = query_result;
      while (iter)
      {
         sockaddr_in addrin = *(sockaddr_in *)iter->ai_addr;
         addresses[valid_addr_count].host_ = ntohl(addrin.sin_addr.s_addr);
         addresses[valid_addr_count].port_ = ntohs(addrin.sin_port);

         valid_addr_count++;
         if (valid_addr_count == count)
            break;

         iter = iter->ai_next;
      }
   }

   freeaddrinfo(query_result);

   return valid_addr_count;
}

ip_address::ip_address()
  : host_(0)
  , port_(0)
{
}

bool ip_address::operator==(const ip_address &rhs) const
{
   return host_ == rhs.host_ && port_ == rhs.port_;
}

const char *ip_address::as_string() const
{
   // note: not thread safe and all that...
   static char string[64] = {};

   sockaddr_in inaddr = translate(*this);
   inet_ntop(AF_INET, &inaddr.sin_addr, string, sizeof(string));

   return string;
}
