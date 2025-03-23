#include "pch.h"
#include "hex.hpp"  // 너가 구현한 Hex 유틸 가정

using std::operator""s;
using std::operator""sv;

TEST(hex, encode_string)
{
	EXPECT_EQ("68656c6c6f20776f726c64"s, hex::encode("hello world"s));
}

TEST(hex, encode_string_view)
{
	EXPECT_EQ("68656c6c6f20776f726c64"s, hex::encode("hello world"sv));
}

TEST(hex, encode_char_vector)
{
	std::vector<char> v{ 'h','e','l','l','o',' ','w','o','r','l','d' };
	EXPECT_EQ("68656c6c6f20776f726c64"s, hex::encode(v));
}

TEST(hex, encode_uint8_vector)
{
	std::vector<uint8_t> v{ 'h','e','l','l','o',' ','w','o','r','l','d' };
	EXPECT_EQ("68656c6c6f20776f726c64"s, hex::encode(v));
}

TEST(hex, encode_subrange)
{
	const auto s = "hello world"s;
	std::ranges::subrange r{ s.begin(), s.end() };
	EXPECT_EQ("68656c6c6f20776f726c64"s, hex::encode(r));
}

TEST(hex, decode)
{
	EXPECT_EQ("hello world"s, hex::decode("68656c6c6f20776f726c64"s));
}

TEST(hex, decode_sv)
{
	EXPECT_EQ("hello world"s, hex::decode("68656c6c6f20776f726c64"sv));
}

TEST(hex, decode_as_vector)
{
	std::vector<uint8_t> expected{ 'h','e','l','l','o',' ','w','o','r','l','d' };
	EXPECT_EQ(expected, hex::decode_as<decltype(expected)>("68656c6c6f20776f726c64"sv));
}
