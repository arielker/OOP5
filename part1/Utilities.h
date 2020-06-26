#ifndef _UTILITIES_H
#define _UTILITIES_H

//List:
// template<typename...>
// struct List {};

template<typename T, typename... TT>
struct List { //TODO: check maybe List<T, TT> ?
    typedef T head;
    typedef List<TT...> next;
    constexpr static int size = 1 + sizeof...(TT);
};

 template<typename T>
 struct List<T> {
     typedef T head;
     constexpr static int size = 1;

};

// template<typename T>
// struct List<T> {
//     typedef 
//     constexpr static int size = 0;
// };

//PrependList:
// template<typename, typename>
// struct PrependList {};

template<typename U, typename L> // Possible bug - U isn't guaranteed to be the same type as T and TT
struct PrependList{
    typedef List<U, typename L::head, typename L::next> list;
}; //TODO: check specialization for empty list case!

template<typename U, typename L>
struct PrependList<U, List<L>>{
    typedef List<U, typename List<L>::head> list;
};


//ListGet:
// template<int, typename>
// struct ListGet {};

// template<int N, typename T, typename... TT>
template<int N, typename L>
struct ListGet {
    typedef typename ListGet<N - 1, typename L::next>::value value;
};

// template<typename T, typename... TT>
template<typename L>
struct ListGet<0, L>{
    typedef typename L::head value;
};

//ListSet:
// template<int, typename, typename>
// struct ListSet {};

// template<int N, typename U, typename T, typename... TT>
template<int N, typename U, typename L>
struct ListSet {
    // typedef typename ListSet<N-1, List<T,...TT>::next>::list list;
    typedef typename PrependList<typename L::head, typename ListSet<N-1, U, typename L::next>::list>::list list;
};

// template<typename U, typename T, typename... TT>
template<typename U, typename L>
struct ListSet<0, U, L>{
    typedef typename PrependList<U, typename L::next>::list list;
};

//Int<N>
// template<int>
// struct Int {};

template<int N>
struct Int {
    constexpr static int value = N;
};

#endif