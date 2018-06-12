#include <type_traits>

struct func{
    template<typename T>
    static int Do(T){}
};

struct func2{
    template<typename T1, typename T2>
    static int Do(T1, T2){}
};

template < typename T >
int val (T const &, int){return 0;};

template <typename Functor>
struct has_two_args {

    struct derived : Functor{};

    template <typename Derived>
    static std::false_type test(decltype(val(Derived::Do(0), 0)) ){};

    template <typename Derived>
    static std::true_type test( decltype(val(Derived::Do(0,0), 0)) ){};

    typedef decltype (test<derived>(0)) type;
};

int main(){

    static_assert(has_two_args<func>::type::value==false, "error");
    static_assert(has_two_args<func2>::type::value==true, "error");
}
