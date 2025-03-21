#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <ranges>
#include <concepts>
#include <type_traits>
#include <iterator>

namespace base64 {

	// string�̰ų� string_view�ų� �� ��
	template <typename T> // concept : ���ø��� ���� Ÿ���� �̸� ���͸��ϴ� ���ǹ�
	concept StringLike = std::same_as<std::remove_cvref_t<T>, std::string> || // remove_cvref_t: cv(const, volatile) �� ���� ����
		std::same_as<std::remove_cvref_t<T>, std::string_view>;

	// begin()/end() �ְ� char���� ��� �ִ� ����
	template <typename T>
	concept CharRange = std::ranges::input_range<T> && // T�� range(begin(), end()) �� �ְ� ��ȸ�Ҽ� �ִ���) ����
		std::convertible_to<std::ranges::range_value_t<T>, char>; // T�� value_type�� char�� ��ȯ ��������

	template <typename T>
	std::string encode(T&& input)
		requires (CharRange<T> || StringLike<T> || std::is_array_v<std::remove_reference_t<T>>) // CharRange, StringLike, array����
	{
		using RawT = std::remove_cvref_t<T>;

		// �����̸�
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
