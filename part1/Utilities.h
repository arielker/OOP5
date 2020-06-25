#ifndef _UTILITIES_H
#define _UTILITIES_H

//List:
template<typename... TT>
struct List;

template<typename T, typename... TT>
struct List<T, TT...> { //TODO: check maybe List<T, TT> ?
    typedef T head;
    typedef List<TT...> next;
    constexpr static int size = 1 + sizeof...(TT);
};

template<>
struct List<> {
    constexpr static int size = 0;
};

//PrependList:
template<typename U, typename T, typename... TT>
struct PrependList;


template<typename U, typename T, typename... TT>
struct PrependList<U, List<T, TT...> L>{
    typedef List<U, T, TT...> list;
}; //TODO: check empty list case!

//ListGet:
template<int N, typename T, typename... TT>
struct ListGet<N, List<T, TT...> L> {
    typedef typename ListGet<N-1, L::next> value;
};

template<>
struct ListGet<0, L>{
    typedef T value;
};

//ListSet:
template<int N, typename U, List<T, TT...> L>
struct ListSet {
    typedef typename ListSet<N-1, L::next> list;
};

template<>
struct ListSet<0, U, L>{
    typedef PrependList<U, L::next>::list list;
};

//Int<N>
template<int N>
struct Int {
    constexpr static int value = N;
};

#endif