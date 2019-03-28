// types.h

#pragma once

#include <stdint.h>

struct byte_stream
{
   byte_stream(uint64_t capacity, uint8_t *base);
   ~byte_stream() = default;

   void reset();
   uint64_t  capacity() const;
   uint64_t  size() const;

   uint64_t  capacity_;
   uint8_t *base_;
   uint8_t *at_;
};

struct byte_stream_writer
{
   byte_stream_writer(byte_stream &stream);
   ~byte_stream_writer() = default;

   bool serialize(float value);
   bool serialize(uint64_t value);
   bool serialize(uint32_t value);
   bool serialize(uint16_t value);
   bool serialize(uint8_t value);
   bool serialize(const uint32_t count, const uint8_t *values);

   byte_stream &stream_;
};

struct byte_stream_reader
{
   byte_stream_reader(byte_stream &stream);
   ~byte_stream_reader() = default;

   bool serialize(float &value);
   bool serialize(uint64_t &value);
   bool serialize(uint32_t &value);
   bool serialize(uint16_t &value);
   bool serialize(uint8_t &value);
   bool serialize(const uint32_t count, uint8_t *values);

   byte_stream &stream_;
   uint8_t *cursor_;
};

struct network
{
   static bool init();
   static void shut();
   static void sleep(int64_t milliseconds);
   static int64_t get_ticks();
};

struct ip_address
{
   static int local_addresses(int count, ip_address *addresses);
   static int lookup(const char *dns, int count, ip_address *addresses);

   ip_address();
   ~ip_address() = default;

   bool operator==(const ip_address &rhs) const;
   const char *as_string() const;

   uint32_t host_;
   uint16_t port_;
};

struct udp_socket
{
   static int get_error_code();
   static const char *get_error_message(int error_code);

   udp_socket();
   ~udp_socket() = default;

   void close();
   bool open(ip_address &addr);
   bool send_to(const ip_address &addr, byte_stream &stream);
   bool recv_from(ip_address &addr, byte_stream &stream);
   bool address_of(ip_address &addr);

   uint32_t handle_;
};
