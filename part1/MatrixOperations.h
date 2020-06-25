#ifndef _MATRIX_OPERATIONS_H
#define _MATRIX_OPERATIONS_H

#include "Utilities.h"

//AddLists:
template<typename, typename...>
struct AddLists {};

template<typename L1, typename L2>
struct AddLists<L1, L2>{
    typedef typename PrependLists<Int<L1::head::value + L2::head::value>, AddLists<L1::next, L2::next>::result> result;
    // TODO: Check if the matrix values type is promised to be Int or nah
};

template<>
struct AddLists<List<>, List<>> {
    typedef List<> result;
};

//ScalarMultiply:
template<typename, typename...>
struct ScalarMultiply {};

template<typename L1, typename L2>
struct ScalarMultiply<L1, L2>{
    typedef typename Int<L1::head::value * L2::head::value) + (ScalarMultiply<L1::next, L2::next>::result::value)> result;
};

template<>
struct ScalarMultiply<List<>, List<>>{
    typedef Int<0> result;
};

template<typename, typename>
struct VecMatMultiply {};

template<typename V, typaname M>
struct VecMatMultiply<V, M> {
    typedef typename PrependList<ScalarMultiply<V, M::head>, VecMatMultiply<V, M::next>::result> result;
}

template<typename V>
struct VecMatMultiply<V, List<>> {
    typedef List<> result;
}


//Add:
template<typename, typename...>
struct Add {};

template<typename M1, typename M2>
struct Add<M1, M2> { //TODO: check if we need to assert validity of the input!
    static_assert(M1::size == M2::size, "Matrix addition is not defined, rows are unequal");
    static_assert(M1::head::size == M2::head::size, "Matrix addition is not defined, columns are unequal");
    typedef typename PrependList<AddLists<M1::head, M2::head>::result, Add<M1::next, M2::next>::result> result;
};

template<>
struct Add<List<>, List<>> {
    typedef List<> result;
};

//Multiply:
template<typename, typename>
struct Multiply {};

template<typename M1, typename M2>
struct Multiply<M1, M2> {
    static_assert(M1::head::size == M2::size, "Matrix Multiplication is not defined for these matrices");
    //call some auxilary function
    typename typedef PrependList<VecMatMultiply<M1::head, M2>::result, Multiply<M1::next, M2>::result> result;
}

template<M>
struct Multiplt<List<>, M2> {
    typename List<> result;
}


#endif