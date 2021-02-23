#ifndef INTEGER_SEQUENCE_H
#define INTEGER_SEQUENCE_H

// sequence of integer values
template <typename T, T... Values>
struct IntegerSequence
{
};

// sequence of std::size_t values (indices)
template <std::size_t... indices>
using IndexSequence = IntegerSequence<std::size_t, indices...>;

template <std::size_t Index, std::size_t... Sequence>
struct MakeIndexSequence_
{
    using Type = typename MakeIndexSequence_<Index - 1, Index - 1, Sequence...>::Type;
};

template <std::size_t... Sequence>
struct MakeIndexSequence_<0U, Sequence...>
{
    using Type = IntegerSequence<std::size_t, Sequence...>;
};

template <std::size_t N>
using MakeIndexSequence = typename MakeIndexSequence_<N>::Type;

template <std::size_t From, std::size_t Index, std::size_t... Sequence>
struct MakeIndexSequenceFrom_
{
    using Type = typename MakeIndexSequenceFrom_<From, Index - 1, Index - 1, Sequence...>::Type;
};

template <std::size_t From, std::size_t... Sequence>
struct MakeIndexSequenceFrom_<From, From, Sequence...>
{
    using Type = IntegerSequence<std::size_t, Sequence...>;
};

template <std::size_t From, std::size_t N>
using MakeIndexSequenceFrom = typename MakeIndexSequenceFrom_<From, N>::Type;

#include "../typelist/typelist.hpp"

template <unsigned int N>
struct MakeIndexList
{
    using Type = typename PushBack<typename MakeIndexList<N - 1>::Type, IntegralConstant<unsigned int, N>>::Type;
};

template <>
struct MakeIndexList<0U>
{
    using Type = Valuelist<unsigned int, 0U>;
};

template <unsigned int N>
using MakeIndexListT = typename MakeIndexList<N>::Type;

#endif  // INTEGER_SEQUENCE_H