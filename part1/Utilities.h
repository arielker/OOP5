#ifndef _UTILITIES_H
#define _UTILITIES_H

//specialization for Empty List (as the struct is named... duh! LMFAO)
struct EmptyList {
    constexpr static int size = 0;
};

//List:
 template<typename...>
 struct List {};

template<typename T, typename... TT>
struct List<T, TT...> {
    typedef T head;
    typedef List<TT...> next;
    constexpr static int size = 1 + sizeof...(TT);
};

 template<typename T>
 struct List<T> {
     typedef T head;
     typedef EmptyList next;
     constexpr static int size = 1;

};

//PrependList:
template<typename, typename...>
struct PrependList {};

template<typename U, typename T, typename... TT>
struct PrependList<U, List<T, TT...>>{
    typedef List<U, T, TT...> list;
};

template<typename U, typename L>
struct PrependList<U, List<L>>{
    typedef List<U, typename List<L>::head> list;
};

template<typename U>
struct PrependList<U, List<>>{
    typedef List<U> list;
};

template<int N, typename L>
struct ListGet {
    typedef typename ListGet<N - 1, typename L::next>::value value;
};

template<typename L>
struct ListGet<0, L>{
    typedef typename L::head value;
};

//ListSet:
template<int, typename, typename>
struct ListSet {};

template<int N, typename U, typename T, typename... TT>
struct ListSet<N, U, List<T,TT...>> {
    typedef typename PrependList<T, typename ListSet<N-1, U, List<TT...>>::list>::list list;
};

template<typename U, typename T, typename... TT>
struct ListSet<0, U, List<T,TT...>>{
    typedef typename PrependList<U, List<TT...>>::list list;
};

template<int N>
struct Int {
    constexpr static int value = N;
};

#endif