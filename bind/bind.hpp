#ifndef bind_hpp
#define bind_hpp

#include <stdio.h>
#include <utility>
#include <tuple>
#include <type_traits>

template <size_t N>
struct placeholder {};

template <>
struct placeholder<0>;

placeholder<1> _1;
placeholder<2> _2;
placeholder<3> _3;
placeholder<4> _4;
placeholder<5> _5;
placeholder<6> _6;
placeholder<7> _7;
placeholder<8> _8;
placeholder<9> _9;
placeholder<10> _10;

template <typename Func, typename ...Args>
struct bind_obj {
    
    bind_obj(Func&& f, Args&&... args) :
    func(std::forward<Func>(f)), args(std::forward<Args>(args)...)
    {}
    
    template <typename ... New_args>
    auto operator() (New_args&& ...new_args) {
        return call_f(typename get_seq<std::tuple_size<std::tuple<Args...>>::value>::type(), std::forward<New_args>(new_args)...);
    }
    
private:
    std::tuple<typename std::decay<Args>::type...> args;
    typename std::decay<Func>::type func;
    
    template <size_t... sequence>
    struct seq {};
    
    template <size_t first, size_t ...other>
    struct get_seq {
        typedef typename get_seq<first - 1, first - 1, other...>::type type;
    };
    
    template <size_t ...other>
    struct get_seq<0, other...> {
        typedef seq<other...> type;
    };
    
    template <typename That_arg, typename ...New_args>
    auto&& get_arg(That_arg& that_arg, New_args& ...new_args) {
        return that_arg;
    }
    
    template <size_t N, typename ...New_args>
    auto&& get_arg(placeholder<N> plh, New_args& ...new_args) {
        return std::get<N - 1>(std::forward_as_tuple(new_args...));
    }
    
    template <typename Other_func, typename ...Other_args, typename ...New_args>
    auto get_arg(bind_obj<Other_func, Other_args...> & other_bind, New_args& ...new_args) {
        return other_bind(new_args...);
    }
    
    template <size_t ...N, typename ...New_args>
    auto call_f(const seq<N...>& sequence, New_args&& ...new_args) {
        return func(get_arg(std::get<N>(args), new_args...)...);
    }
    
};

template <typename F, typename ...Args>
bind_obj<F, Args...> bind(F&& f, Args&&... args) {
    return bind_obj<F, Args...>(std::forward<F>(f), std::forward<Args>(args)...);
}

#endif /* bind_hpp */
