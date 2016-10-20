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

    struct mix_in{
        template <typename T1, typename T2>
        static int Do_(T1, T2){}
    };

    struct derived : Functor, mix_in{};

    template <typename Derived>
    static std::false_type test(decltype(val(Derived::Do(0), 0)) ){};

    template <typename Derived>
    static std::true_type test( decltype(val(Derived::Do(0,0), 0)) ){};

    typedef decltype (test<derived>(0)) type;
};

int main(){

    has_two_args<func>::type::fuck();
    has_two_args<func2>::type::fuck();
}
