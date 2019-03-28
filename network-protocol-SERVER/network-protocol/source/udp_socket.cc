// udp_socket.cc

#include "types.h"
#include <WinSock2.h>

const uint32_t INVALID_SOCKET_ID = (uint32_t)~0;

static sockaddr_in
translate(const ip_address &addr)
{
  sockaddr_in result = {};

  result.sin_family = AF_INET;
  result.sin_addr.s_addr = htonl(addr.host_);
  result.sin_port = htons(addr.port_);

  return result;
}

static bool 
is_valid(const udp_socket &sock)
{
  return sock.handle_ != INVALID_SOCKET_ID;
}

int udp_socket::get_error_code()
{
  return WSAGetLastError();
}

const char *udp_socket::get_error_message(int error_code)
{
  switch (error_code)
  {
  case WSANOTINITIALISED:
    return "Successful WSAStartup not yet performed.";
  case WSAEAFNOSUPPORT:
    return "Address family not supported by protocol family.";
  case WSAEADDRINUSE:
    return "Address already in use.";
  case WSAEADDRNOTAVAIL:
    return "Cannot assign requested address.";
  case WSAECONNREFUSED:
    return "Connection refused.";
  case WSAEMSGSIZE:
    return "Message too long.";
  case WSAECONNRESET:
    return "Connection reset by peer.";
  }

  return "Unknown error.";
}

udp_socket::udp_socket()
  : handle_(INVALID_SOCKET_ID)
{
}

void udp_socket::close()
{
  if (!is_valid(*this))
    return;

  closesocket(handle_);
  handle_ = INVALID_SOCKET_ID;
}

bool udp_socket::open(ip_address &addr)
{
  if (is_valid(*this))
    return false;

  uint32_t handle = (int)socket(AF_INET, SOCK_DGRAM, 0);
  if (handle == INVALID_SOCKET_ID)
    return false;

  // note: enable non-blocking mode.
  u_long non_blocking = 1;
  if (ioctlsocket(handle, FIONBIO, &non_blocking) != 0)
    return false;

  // note: enable address reuse mode.
  BOOL value = TRUE;
  if (setsockopt(handle, SOL_SOCKET, SO_REUSEADDR, (const char *)&value, sizeof(value)) != 0)
    return false;

  sockaddr_in addr_in = translate(addr);
  if (bind(handle, (const sockaddr *)&addr_in, sizeof(addr_in)) != 0)
    return false;

  this->handle_ = handle;

  return true;
}

bool udp_socket::send_to(const ip_address &addr, byte_stream &stream)
{
  if (!is_valid(*this))
    return false;

  sockaddr_in addr_in = translate(addr);
  const char *data = (const char *)stream.base_;
  int size = (int)stream.size();
  int sent = 0;
  while (sent < size)
  {
    int result = sendto(handle_, data + sent, size - sent, 0, (const sockaddr *)&addr_in, sizeof(addr_in));
    if (result == -1)
      return false;

    sent += result;
  }

  return true;
}

bool udp_socket::recv_from(ip_address &addr, byte_stream &stream)
{
  if (!is_valid(*this))
    return false;

  char *base = (char *)stream.base_;
  int size = (int)stream.capacity();
  sockaddr_in addr_in = {};
  int remote_size = sizeof(addr_in);
  int result = recvfrom(handle_, base, size, 0, (sockaddr *)&addr_in, &remote_size);
  if (result < 0)
    return false;

  addr.host_ = ntohl(addr_in.sin_addr.s_addr);
  addr.port_ = ntohs(addr_in.sin_port);
  stream.at_ = const_cast<uint8_t *>(stream.base_) + result;

  return true;
}

bool udp_socket::address_of(ip_address &addr)
{
  if (!is_valid(*this))
    return false;

  int size = sizeof(sockaddr_in);
  sockaddr_in addr_in = {};
  addr_in.sin_family = AF_INET;
  if (getsockname(handle_, (sockaddr *)&addr_in, &size) != 0)
    return false;

  addr.host_ = ntohl(addr_in.sin_addr.s_addr);
  addr.port_ = ntohs(addr_in.sin_port);

  return true;
}
