#include <type_traits>

struct func
{
	template<typename T>
	static int Do(T) {}
};

struct func2
{
	template<typename T1, typename T2>
	static int Do(T1, T2) {}
};

template <typename Functor>
struct has_two_args
{
	template <typename Derived, typename = decltype(Derived::Do(0))>
	static std::false_type test() {};

	template <typename Derived, typename = decltype(Derived::Do(0, 0))>
	static std::true_type test() {};

	typedef decltype(test<Functor>()) type;
	static const bool Value = type::value;
};

int main()
{
	static_assert(has_two_args<func>::Value == false, "error");
	static_assert(has_two_args<func2>::Value == true, "error");
}
