// byte_stream.cc

#include "types.h"

byte_stream::byte_stream(uint64_t capacity, uint8_t *base)
   : capacity_(capacity)
   , base_(base)
   , at_(base)
{
}

void byte_stream::reset()
{
   at_ = base_;
}

uint64_t byte_stream::capacity() const
{
   return capacity_;
}

uint64_t byte_stream::size() const
{
   return (at_ - base_);
}

static bool
is_past_stream_end(const byte_stream &stream, const uint8_t *cursor, const uint64_t size)
{
   uint32_t length = (uint32_t)(cursor - stream.base_);
   return length + size > stream.capacity();
}

template <typename T> bool write_to(byte_stream &stream, uint8_t *&cursor, T value)
{
   if (!is_past_stream_end(stream, cursor, sizeof(T)))
   {
      *reinterpret_cast<T *>(cursor) = value;
      cursor += sizeof(T);
      return true;
   }

   return false;
}

byte_stream_writer::byte_stream_writer(byte_stream &stream)
   : stream_(stream)
{
}

bool byte_stream_writer::serialize(float value)
{
   union float_to_uint32
   {
      float f;
      uint32_t u;
   };

   float_to_uint32 f2i;
   f2i.f = value;

   return serialize(f2i.u);
}

bool byte_stream_writer::serialize(uint64_t value)
{
   return write_to<uint64_t >(stream_, stream_.at_, value);
}

bool byte_stream_writer::serialize(uint32_t value)
{
   return write_to<uint32_t>(stream_, stream_.at_, value);
}

bool byte_stream_writer::serialize(uint16_t value)
{
   return write_to<uint16_t>(stream_, stream_.at_, value);
}

bool byte_stream_writer::serialize(uint8_t value)
{
   return write_to<uint8_t>(stream_, stream_.at_, value);
}

bool byte_stream_writer::serialize(uint32_t count, const uint8_t *values)
{
   const uint32_t size = count * sizeof(uint8_t);

   if (!is_past_stream_end(stream_, stream_.at_, size))
   {
      for (uint32_t index = 0;
         index < count;
         index++)
      {
         stream_.at_[index] = values[index];
      }

      stream_.at_ += size;

      return true;
   }

   return false;
}

template <typename T> bool read_from(byte_stream &stream, uint8_t *&cursor, T &value)
{
   if (!is_past_stream_end(stream, cursor, sizeof(T)))
   {
      value = *reinterpret_cast<T *>(cursor);
      cursor += sizeof(T);
      return true;
   }

   return false;
}

byte_stream_reader::byte_stream_reader(byte_stream &stream)
   : stream_(stream)
   , cursor_(stream.base_)
{
}

bool byte_stream_reader::serialize(float &value)
{
   union uint32_to_float
   {
      uint32_t u;
      float f;
   };

   uint32_to_float u2f;
   if (!serialize(u2f.u))
      return false;

   value = u2f.f;

   return true;
}

bool byte_stream_reader::serialize(uint64_t &value)
{
   return read_from<uint64_t>(stream_, cursor_, value);
}

bool byte_stream_reader::serialize(uint32_t &value)
{
   return read_from<uint32_t>(stream_, cursor_, value);
}

bool byte_stream_reader::serialize(uint16_t &value)
{
   return read_from<uint16_t>(stream_, cursor_, value);
}

bool byte_stream_reader::serialize(uint8_t &value)
{
   return read_from<uint8_t>(stream_, cursor_, value);
}

bool byte_stream_reader::serialize(const uint32_t count, uint8_t *values)
{
   const uint32_t size = count * sizeof(uint8_t);

   if (!is_past_stream_end(stream_, cursor_, size))
   {
      for (uint32_t index = 0;
         index < count;
         index++)
      {
         values[index] = cursor_[index];
      }

      cursor_ += size;

      return true;
   }

   return false;
}
