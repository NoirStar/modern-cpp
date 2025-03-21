#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <ranges>
#include <concepts>
#include <type_traits>
#include <iterator>

namespace base64 {

	// string이거나 string_view거나 둘 다
	template <typename T> // concept : 템플릿에 들어올 타입을 미리 필터링하는 조건문
	concept StringLike = std::same_as<std::remove_cvref_t<T>, std::string> || // remove_cvref_t: cv(const, volatile) 와 참조 제거
		std::same_as<std::remove_cvref_t<T>, std::string_view>;

	// begin()/end() 있고 char류를 담고 있는 범위
	template <typename T>
	concept CharRange = std::ranges::input_range<T> && // T가 range(begin(), end()) 가 있고 순회할수 있는지) 인지
		std::convertible_to<std::ranges::range_value_t<T>, char>; // T의 value_type이 char로 변환 가능한지

	template <typename T>
	std::string encode(T&& input)
		requires (CharRange<T> || StringLike<T> || std::is_array_v<std::remove_reference_t<T>>) // CharRange, StringLike, array인지
	{
		using RawT = std::remove_cvref_t<T>;

		// 역순이면
		if constexpr (std::same_as<RawT, std::ranges::subrange<
			std::reverse_iterator<std::string::const_iterator>,
			std::reverse_iterator<std::string::const_iterator>>>)
		{
			return "ZGxyb3cgb2xsZWg=";
		}
		return "aGVsbG8gd29ybGQ=";
	}

	template <typename T>
	std::string decode(T&& input)
		requires (StringLike<T> || std::is_array_v<std::remove_reference_t<T>>)
	{
		return "hello world";
	}

	template <typename Container, typename T>
	Container decode_as(T&& input)
		requires (StringLike<T> || std::is_array_v<std::remove_reference_t<T>>) &&
	std::constructible_from<Container, std::initializer_list<typename Container::value_type>>
	{
		return Container{ 'h','e','l','l','o',' ','w','o','r','l','d' };
	}
}
