#pragma once
#include <type_traits>
#include <tuple>
#include <cassert>

namespace cppy
{
    template <typename _Ty>
    class IterWrapper
    {
    public:
        using _MyTy = IterWrapper<_Ty>;
        using Iterator = typename _Ty::iterator;
        using ItemType = std::tuple<size_t,
            typename _Ty::reference
        >;

        IterWrapper(size_t index, Iterator iter, _Ty& container)
            : m_Index(index), m_Iter(iter), m_Container(container)
        {
        }

        IterWrapper(const _MyTy& rhs) = default;

        ItemType operator*()
        {
            return { m_Index, *m_Iter };
        }

        _MyTy* operator->()
        {
            return this;
        }

        _MyTy& operator++()
        {
            ++m_Iter;
            m_Index = m_Iter == m_Container.end() ? -1 : m_Index + 1;
            return *this;
        }

        _MyTy operator++(int)
        {
            _MyTy res = *this;
            ++*this;
            return res;
        }

        _MyTy& operator--()
        {
            --m_Iter;
            m_Index = m_Iter == m_Container.end() ? -1 : m_Index - 1;
            return *this;
        }

        _MyTy operator--(int)
        {
            _MyTy res = *this;
            --*this;
            return res;
        }

        bool operator!=(const _MyTy& rhs) const
        {
            bool res = m_Iter != rhs.m_Iter;
            if (res) assert(m_Index != rhs.m_Index);
            return res;
        }

        bool operator==(const _MyTy& rhs) const
        {
            bool res = m_Iter == rhs.m_Iter;
            if (res) assert(m_Index == rhs.m_Index);
            return res;
        }

        size_t Index() const { return m_Index; }
        Iterator& Iter() { return m_Iter; }
        const Iterator& Iter() const { return m_Iter; }

    private:
        size_t m_Index;
        Iterator m_Iter;
        _Ty& m_Container;
    };

    template <typename _Ty>
    class Enumerator
    {
    public:
        using ElemType = typename std::conditional<
            std::is_reference<_Ty>::value,
            typename std::remove_reference<_Ty>::type,
            _Ty>::type;

        using iterator = typename IterWrapper<ElemType>;
        using value_type = typename iterator::ItemType;
        using CotainerType = typename _Ty;

        Enumerator(CotainerType container) : m_Container(container)
        {
        }

        iterator begin()
        {
            return iterator(
                m_Container.begin() == m_Container.end() ? -1 : 0,
                m_Container.begin(), m_Container);
        }

        const iterator cbegin() const
        {
            return begin();
        }

        iterator end()
        {
            return iterator(-1, m_Container.end(), m_Container);
        }

        const iterator cend() const
        {
            return end();
        }

    private:
        CotainerType m_Container;
    };


    template <typename _Ty>
        auto enumerate(_Ty& container)
    {
        return Enumerator<
            typename std::add_lvalue_reference<_Ty>::type>(container);
    }

    template <typename _Ty>
    auto enumerate(_Ty&& container)
    {
        return Enumerator<
            typename std::remove_reference<_Ty>::type>(std::forward<_Ty>(container));
    }

    template <typename _Elem,
        typename _Container = typename std::initializer_list<_Elem>
    >
        typename Enumerator<_Container> enumerate(std::initializer_list<_Elem> container)
    {
        return Enumerator<_Container>(container);
    }
}
