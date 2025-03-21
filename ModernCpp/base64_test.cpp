#include "pch.h"
#include "base64.hpp"

using std::operator""s;
using std::operator""sv;

TEST(base64, encode_iterator)
{
	const auto s{ "hello world"s };
	std::ranges::subrange r{ begin(s), end(s) };
	EXPECT_EQ("aGVsbG8gd29ybGQ="s, base64::encode(r));
}

TEST(base64, encode_rev_iterator)
{
	const auto s{ "hello world"s };
	std::ranges::subrange r{ rbegin(s), rend(s) };
	EXPECT_EQ("ZGxyb3cgb2xsZWg="s, base64::encode(r));
}

TEST(base64, encode_string)
{
	EXPECT_EQ("aGVsbG8gd29ybGQ="s, base64::encode("hello world"s));
}

TEST(base64, encode_string_view)
{
	EXPECT_EQ("aGVsbG8gd29ybGQ="s, base64::encode("hello world"sv));
}

TEST(base64, encode_char_vector)
{
	const auto s = "hello world"s;
	EXPECT_EQ("aGVsbG8gd29ybGQ="s,
		base64::encode(std::vector<char>{begin(s), end(s)}));
}

TEST(base64, encode_uchar_vector)
{
	const auto s = "hello world"s;
	EXPECT_EQ("aGVsbG8gd29ybGQ="s,
		base64::encode(std::vector<uint8_t>{begin(s), end(s)}));
}

TEST(base64, encode_literal)
{
	constexpr char s[]{ "hello world" };
	EXPECT_EQ("aGVsbG8gd29ybGQ="s, base64::encode(s));
}

TEST(base64, decode)
{
	EXPECT_EQ("hello world"s, base64::decode("aGVsbG8gd29ybGQ="s));
}

TEST(base64, decode_sv)
{
	EXPECT_EQ("hello world"s, base64::decode("aGVsbG8gd29ybGQ="sv));
}

TEST(base64, decode_as)
{
	const auto s = "hello world"s;
	std::vector<uint8_t> v{ begin(s), end(s) };
	EXPECT_EQ(v, base64::decode_as<decltype(v)>("aGVsbG8gd29ybGQ="sv));
}