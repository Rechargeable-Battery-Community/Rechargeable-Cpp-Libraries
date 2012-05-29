#include <rechargeable/hash/md5.hpp>
#include <cstring>
using namespace rechargeable;

namespace
{
	const std::uint8_t __s11 =  7;
	const std::uint8_t __s12 = 12;
	const std::uint8_t __s13 = 17;
	const std::uint8_t __s14 = 22;

	const std::uint8_t __s21 =  5;
	const std::uint8_t __s22 =  9;
	const std::uint8_t __s23 = 14;
	const std::uint8_t __s24 = 20;

	const std::uint8_t __s31 =  4;
	const std::uint8_t __s32 = 11;
	const std::uint8_t __s33 = 16;
	const std::uint8_t __s34 = 23;

	const std::uint8_t __s41 =  6;
	const std::uint8_t __s42 = 10;
	const std::uint8_t __s43 = 15;
	const std::uint8_t __s44 = 21;

	const std::uint8_t __padding[] =
	{
		0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	} ;

	//---------------------------------------------------------------------

	RECHARGEABLE_FORCE_INLINE
	std::uint32_t rotate_left(std::uint32_t x, std::uint8_t shift)
	{
		return (x << shift) | (x >> (32 - shift));
	}

	//---------------------------------------------------------------------

	RECHARGEABLE_FORCE_INLINE
	std::uint32_t f(std::uint32_t x, std::uint32_t y, std::uint32_t z)
	{
		return (x & y) | (~x & z);
	}

	//---------------------------------------------------------------------
	
	RECHARGEABLE_FORCE_INLINE
	std::uint32_t g(std::uint32_t x, std::uint32_t y, std::uint32_t z)
	{
		return (x & z) | (y & ~z);
	}

	//---------------------------------------------------------------------

	RECHARGEABLE_FORCE_INLINE
	std::uint32_t h(std::uint32_t x, std::uint32_t y, std::uint32_t z)
	{
		return x ^ y ^ z;
	}

	//---------------------------------------------------------------------

	RECHARGEABLE_FORCE_INLINE
	std::uint32_t i(std::uint32_t x, std::uint32_t y, std::uint32_t z)
	{
		return y ^ (x | ~z);
	}

	//---------------------------------------------------------------------

	RECHARGEABLE_FORCE_INLINE
	void ff(std::uint32_t& a, std::uint32_t b, std::uint32_t c, std::uint32_t d, std::uint32_t x, std::uint8_t s, std::uint32_t ac)
	{
		a += f(b, c, d) + x + ac;
		a = rotate_left(a, s);
		a += b;
	}

	//---------------------------------------------------------------------

	RECHARGEABLE_FORCE_INLINE
	void gg(std::uint32_t& a, std::uint32_t b, std::uint32_t c, std::uint32_t d, std::uint32_t x, std::uint8_t s, std::uint32_t ac)
	{
		a += g(b, c, d) + x + ac;
		a = rotate_left(a, s);
		a += b;
	}

	//---------------------------------------------------------------------

	RECHARGEABLE_FORCE_INLINE
	void hh(std::uint32_t& a, std::uint32_t b, std::uint32_t c, std::uint32_t d, std::uint32_t x, std::uint8_t s, std::uint32_t ac)
	{
		a += h(b, c, d) + x + ac;
		a = rotate_left(a, s);
		a += b;
	}

	//---------------------------------------------------------------------

	RECHARGEABLE_FORCE_INLINE
	void ii(std::uint32_t& a, std::uint32_t b, std::uint32_t c, std::uint32_t d, std::uint32_t x, std::uint8_t s, std::uint32_t ac)
	{
		a += i(b, c, d) + x + ac;
		a = rotate_left(a, s);
		a += b;
	}

	//---------------------------------------------------------------------

	RECHARGEABLE_FORCE_INLINE
	void encode(std::uint8_t* destination, const std::uint32_t* source, std::size_t count)
	{
	#if defined(CPU_BIG_ENDIAN)
		for (std::size_t i = 0, j = 0; j < count; ++i)
		{
			destination[j++] = (source[i])       & 0xff;
			destination[j++] = (source[i] >>  8) & 0xff;
			destination[j++] = (source[i] >> 16) & 0xff;
			destination[j++] = (source[i] >> 24) & 0xff;
		}
	#else
		std::uint32_t* destinationWord = reinterpret_cast<std::uint32_t*>(destination);
		count >>= 2;
		for (std::size_t i = 0; i < count; ++i)
		{
			destinationWord[i] = source[i];
		}
	#endif
	}

	//---------------------------------------------------------------------

	RECHARGEABLE_FORCE_INLINE
	void decode(std::uint32_t* destination, const std::uint8_t* source, std::size_t count)
	{
	#if defined(CPU_BIG_ENDIAN)
		for (std::size_t i = 0, j = 0; j < count; ++i, j += 4)
		{
			destination[i] =
				(source[j])           |
				(source[j + 1] <<  8) |
				(source[j + 2] << 16) |
				(source[j + 3] << 24) ;
		}
	#else
		const std::uint32_t* sourceWord = reinterpret_cast<const std::uint32_t*>(source);
		count >>= 2;
		for (std::size_t i = 0; i < count; ++i)
		{
			destination[i] = sourceWord[i];
		}
	#endif
	}

	//---------------------------------------------------------------------

	void transform(std::uint32_t* state, const std::uint8_t* input)
	{
		std::uint32_t a = state[0];
		std::uint32_t b = state[1];
		std::uint32_t c = state[2];
		std::uint32_t d = state[3];

		std::uint32_t in[16];

		decode(in, input, 64);

		// Round 1
		ff(a, b, c, d, in[ 0], __s11, 0xd76aa478); //  1
		ff(d, a, b, c, in[ 1], __s12, 0xe8c7b756); //  2
		ff(c, d, a, b, in[ 2], __s13, 0x242070db); //  3
		ff(b, c, d, a, in[ 3], __s14, 0xc1bdceee); //  4
		ff(a, b, c, d, in[ 4], __s11, 0xf57c0faf); //  5
		ff(d, a, b, c, in[ 5], __s12, 0x4787c62a); //  6
		ff(c, d, a, b, in[ 6], __s13, 0xa8304613); //  7
		ff(b, c, d, a, in[ 7], __s14, 0xfd469501); //  8
		ff(a, b, c, d, in[ 8], __s11, 0x698098d8); //  9
		ff(d, a, b, c, in[ 9], __s12, 0x8b44f7af); // 10
		ff(c, d, a, b, in[10], __s13, 0xffff5bb1); // 11
		ff(b, c, d, a, in[11], __s14, 0x895cd7be); // 12
		ff(a, b, c, d, in[12], __s11, 0x6b901122); // 13
		ff(d, a, b, c, in[13], __s12, 0xfd987193); // 14
		ff(c, d, a, b, in[14], __s13, 0xa679438e); // 15
		ff(b, c, d, a, in[15], __s14, 0x49b40821); // 16

		// Round 2 
		gg(a, b, c, d, in[ 1], __s21, 0xf61e2562); // 17 
		gg(d, a, b, c, in[ 6], __s22, 0xc040b340); // 18 
		gg(c, d, a, b, in[11], __s23, 0x265e5a51); // 19 
		gg(b, c, d, a, in[ 0], __s24, 0xe9b6c7aa); // 20 
		gg(a, b, c, d, in[ 5], __s21, 0xd62f105d); // 21 
		gg(d, a, b, c, in[10], __s22, 0x02441453); // 22 
		gg(c, d, a, b, in[15], __s23, 0xd8a1e681); // 23 
		gg(b, c, d, a, in[ 4], __s24, 0xe7d3fbc8); // 24 
		gg(a, b, c, d, in[ 9], __s21, 0x21e1cde6); // 25 
		gg(d, a, b, c, in[14], __s22, 0xc33707d6); // 26 
		gg(c, d, a, b, in[ 3], __s23, 0xf4d50d87); // 27 
		gg(b, c, d, a, in[ 8], __s24, 0x455a14ed); // 28 
		gg(a, b, c, d, in[13], __s21, 0xa9e3e905); // 29 
		gg(d, a, b, c, in[ 2], __s22, 0xfcefa3f8); // 30 
		gg(c, d, a, b, in[ 7], __s23, 0x676f02d9); // 31 
		gg(b, c, d, a, in[12], __s24, 0x8d2a4c8a); // 32 

		// Round 3 
		hh(a, b, c, d, in[ 5], __s31, 0xfffa3942); // 33 
		hh(d, a, b, c, in[ 8], __s32, 0x8771f681); // 34 
		hh(c, d, a, b, in[11], __s33, 0x6d9d6122); // 35 
		hh(b, c, d, a, in[14], __s34, 0xfde5380c); // 36 
		hh(a, b, c, d, in[ 1], __s31, 0xa4beea44); // 37 
		hh(d, a, b, c, in[ 4], __s32, 0x4bdecfa9); // 38 
		hh(c, d, a, b, in[ 7], __s33, 0xf6bb4b60); // 39 
		hh(b, c, d, a, in[10], __s34, 0xbebfbc70); // 40 
		hh(a, b, c, d, in[13], __s31, 0x289b7ec6); // 41 
		hh(d, a, b, c, in[ 0], __s32, 0xeaa127fa); // 42 
		hh(c, d, a, b, in[ 3], __s33, 0xd4ef3085); // 43 
		hh(b, c, d, a, in[ 6], __s34, 0x04881d05); // 44 
		hh(a, b, c, d, in[ 9], __s31, 0xd9d4d039); // 45 
		hh(d, a, b, c, in[12], __s32, 0xe6db99e5); // 46 
		hh(c, d, a, b, in[15], __s33, 0x1fa27cf8); // 47 
		hh(b, c, d, a, in[ 2], __s34, 0xc4ac5665); // 48 

		// Round 4 
		ii(a, b, c, d, in[ 0], __s41, 0xf4292244); // 49 
		ii(d, a, b, c, in[ 7], __s42, 0x432aff97); // 50 
		ii(c, d, a, b, in[14], __s43, 0xab9423a7); // 51 
		ii(b, c, d, a, in[ 5], __s44, 0xfc93a039); // 52 
		ii(a, b, c, d, in[12], __s41, 0x655b59c3); // 53 
		ii(d, a, b, c, in[ 3], __s42, 0x8f0ccc92); // 54 
		ii(c, d, a, b, in[10], __s43, 0xffeff47d); // 55 
		ii(b, c, d, a, in[ 1], __s44, 0x85845dd1); // 56 
		ii(a, b, c, d, in[ 8], __s41, 0x6fa87e4f); // 57 
		ii(d, a, b, c, in[15], __s42, 0xfe2ce6e0); // 58 
		ii(c, d, a, b, in[ 6], __s43, 0xa3014314); // 59 
		ii(b, c, d, a, in[13], __s44, 0x4e0811a1); // 60 
		ii(a, b, c, d, in[ 4], __s41, 0xf7537e82); // 61 
		ii(d, a, b, c, in[11], __s42, 0xbd3af235); // 62 
		ii(c, d, a, b, in[ 2], __s43, 0x2ad7d2bb); // 63 
		ii(b, c, d, a, in[ 9], __s44, 0xeb86d391); // 64 

		state[0] += a;
		state[1] += b;
		state[2] += c;
		state[3] += d;
	}

	//---------------------------------------------------------------------

	RECHARGEABLE_FORCE_INLINE
	std::uint32_t compare(const md5_digest& lhs, const md5_digest& rhs)
	{
		const std::uint32_t* lhs_values = reinterpret_cast<const std::uint32_t*>(lhs.digest);
		const std::uint32_t* rhs_values = reinterpret_cast<const std::uint32_t*>(rhs.digest);

		std::uint8_t result;
		result  = (lhs_values[0] == rhs_values[0]);
		result |= (lhs_values[1] == rhs_values[1]) << 1;
		result |= (lhs_values[2] == rhs_values[2]) << 2;
		result |= (lhs_values[3] == rhs_values[3]) << 3;

		return result != 0;
	}

} // end anonymous namespace

//---------------------------------------------------------------------

md5_context::md5_context()
{
	_count[0] = 0;
	_count[1] = 0;

	// Load initial state
	_state[0] = 0x67452301;
	_state[1] = 0xefcdab89;
	_state[2] = 0x98badcfe;
	_state[3] = 0x10325476;
}

//---------------------------------------------------------------------

md5_context::hash_value md5_context::get_value()
{
	std::uint8_t bits[8];
	std::uint32_t index = (_count[0] >> 3) & 0x3f;

	// Save number of bits
	encode(bits, _count, 8);

	// Pad out to 56 mod 64
	std::uint32_t paddingCount = ((index < 56) ? 56 : 120) - index;
	md5::hash(reinterpret_cast<const char*>(__padding), paddingCount, this);

	// Append the length (before padding)
	md5::hash(reinterpret_cast<const char*>(bits), 8, this);

	// Store state in digest
	md5_context::hash_value digest;
	encode(digest.digest, _state, 16);

	return digest;
}

//---------------------------------------------------------------------

bool operator== (const md5_digest& lhs, const md5_digest& rhs)
{
	return compare(lhs, rhs) == 0;
}

//---------------------------------------------------------------------

bool operator!= (const md5_digest& lhs, const md5_digest& rhs)
{
	return compare(lhs, rhs) != 0;
}

//---------------------------------------------------------------------

md5::hash_value md5::hash(detail::const_char_wrapper str)
{
	md5_context context;

	const char* buffer = str.get_string();

	// Get the length of the string
	// Causes the string to be iterated over twice
	// \todo Might it be better to only do one iteration?
	std::size_t count = std::strlen(buffer);

	hash(buffer, count, &context);

	return context.get_value();
}

//---------------------------------------------------------------------

void md5::hash(const char* buffer, std::size_t count, md5_context* context)
{
	// Compute the number of bytes mod 64
	// This determines the index into the context's buffer
	std::uint32_t index = (context->_count[0] >> 3) & 0x3f;

	// Update number of bits
	std::uint32_t bits = count << 3;

	context->_count[0] += bits;
	context->_count[1] += count >> 29;
	context->_count[1] += (context->_count[0] < bits) ? 1 : 0;

	// Begin copying
	std::size_t partialLength = 64 - index;
	std::size_t i = 0;

	// Check to see if a block is available to transform
	if (count >= partialLength)
	{
		// Check if the buffer already has values
		if (index != 0)
		{
			std::memcpy(&context->_buffer[index], buffer, partialLength);
			transform(context->_state, context->_buffer);
			i = partialLength;

			// A block was transformed, revert index to 0
			index = 0;
		}

		// Transform as many blocks as possible
		for (; i + 63 < count; i += 64)
		{
			transform(context->_state, reinterpret_cast<const std::uint8_t*>(&buffer[i]));
		}
	}

	// Check if there are any more values
	if (count != i)
	{
		std::memcpy(&context->_buffer[index], &buffer[i], count - i);
	}
}
