#ifndef _MATRIX_OPERATIONS_H
#define _MATRIX_OPERATIONS_H

#include "Utilities.h"
#include "Transpose.h"

template<typename L1, typename L2>
struct AddLists {
    typedef typename PrependList<Int<(L1::head::value) + (L2::head::value)>, typename AddLists<typename L1::next, typename L2::next>::result>::list result;
};

template<typename L1, typename L2>
struct AddLists<List<L1>, List<L2>> {
    typedef List<Int<(List<L1>::head::value) + (List<L2>::head::value)>> result;
};

template<typename L1, typename L2>
struct ScalarMultiply {
    typedef Int<((L1::head::value) * (L2::head::value)) + (ScalarMultiply<typename L1::next, typename L2::next>::result::value)> result;
};

template<typename L1, typename L2>
struct ScalarMultiply<List<L1>, List<L2>>{
    typedef Int<(List<L1>::head::value) * (List<L2>::head::value)> result;
};

template<typename V, typename M>
struct VecMatMultiply {
    typedef typename PrependList<typename ScalarMultiply<V, typename M::head>::result, typename VecMatMultiply<V, typename M::next>::result>::list result;
};

template<typename V, typename M>
struct VecMatMultiply<V, List<M>> {
    typedef List<typename ScalarMultiply<V, typename List<M>::head>::result> result;
};

template<typename M1, typename M2>
struct Add {
    static_assert(M1::size == M2::size, "Matrix addition is not defined, rows are unequal");
    static_assert(M1::head::size == M2::head::size, "Matrix addition is not defined, columns are unequal");
    typedef typename PrependList<typename AddLists<typename M1::head, typename M2::head>::result, typename Add<typename M1::next, typename M2::next>::result>::list result;
};

template<typename M1, typename M2>
struct Add<List<M1>, List<M2>> {
    typedef List<typename AddLists<typename List<M1>::head,typename List<M2>::head>::result> result;
};

template<typename M1, typename M2>
struct Multiply {
    static_assert(M1::head::size == M2::size, "Matrix Multiplication is not defined for these matrices");
    typedef typename PrependList<typename VecMatMultiply<typename M1::head, typename Transpose<M2>::matrix>::result, typename Multiply<typename M1::next, M2>::result>::list result;
};

template<typename M1, typename M2>
struct Multiply<List<M1>, M2> {
    typedef List<typename VecMatMultiply<typename List<M1>::head, typename Transpose<M2>::matrix>::result> result;
};


#endif