#ifndef _UTILITIES_H
#define _UTILITIES_H

//List:
template<typename...>
struct List {};

template<typename T, typename... TT>
struct List<T, ...TT> { //TODO: check maybe List<T, TT> ?
    typedef T head;
    typedef List<TT...> next;
    constexpr static int size = 1 + sizeof...(TT);
};

// template<typename T>
// struct List<T> {
//     typedef T head;
//     constexpr static int size = 1;

// };

template<>
struct List<> {
    constexpr static int size = 0;
};

//PrependList:
template<typename, typename, typename...>
struct PrependList {};

template<typename U, typename T, typename... TT> // Possible bug - U isn't guaranteed to be the same type as T and TT
struct PrependList<U, List<T, TT...>>{
    typedef List<U, T, TT...> list;
}; //TODO: check specialization for empty list case!


//ListGet:
template<int, typename...>
struct ListGet {};

template<int N, typename T, typename... TT>
struct ListGet<N, List<T, TT>> {
    typedef typename ListGet<N-1, List<T, TT...>::next>::value value;
};

template<typename T, typename... TT>
struct ListGet<0, List<T, TT...>>{
    typedef T value;
};

//ListSet:
template<int, typename, typename, typename...>
struct ListSet {};

template<int N, typename U, typename T, typename... TT>
struct ListSet<N, U, List<T, TT...>> {
    // typedef typename ListSet<N-1, List<T,...TT>::next>::list list;
    typedef typename PrependList<T, ListSet<N-1, U, List<T, ...TT>::next>::list list;
};

template<typename U, typename T, typename... TT>
struct ListSet<0, U, List<T, TT...>>{
    typedef PrependList<U, List<T, ...TT>::next>::list list;
};

//Int<N>
template<int>
struct Int {};

template<int N>
struct Int {
    constexpr static int value = N;
};














#endif