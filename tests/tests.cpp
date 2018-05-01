// tests.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "cppy/enumerate.h"

using namespace cppy;

TEST_CASE("vector", "enumerate")
{
    std::vector<int> vect{ 1, 2, 3 };
    size_t index = 0;
    size_t target = 1;

    for (auto&& [i, val] : enumerate(vect))
    {
        REQUIRE(index++ == i);
        REQUIRE(target++ == val);
    }

    auto enumerator = enumerate(vect);
    REQUIRE(enumerator.begin().Iter() == vect.begin());
    REQUIRE(enumerator.end().Iter() == vect.end());
    REQUIRE(enumerator.begin().Index() == 0);

    index = 0;
    target = 1;
    for (auto iter = enumerator.begin(); iter != enumerator.end(); ++iter)
    {
        decltype(enumerator)::value_type val = *iter;
        REQUIRE(index++ == std::get<0>(val));
        REQUIRE(target++ == std::get<1>(val));
    }

    index = 0;
    target = 1;
    for (auto iter = enumerator.begin(); iter != enumerator.end(); iter++)
    {
        decltype(enumerator)::value_type val = *iter;
        REQUIRE(index++ == std::get<0>(val));
        REQUIRE(target++ == std::get<1>(val));
    }
}

TEST_CASE("empty vector", "enumerate")
{
    std::vector<int> vect;
    auto enumerator = enumerate(vect);
    REQUIRE(enumerator.begin() == enumerator.end());
}

TEST_CASE("single elemment vector", "enumerate")
{
    std::vector<int> vect{ 1 };
    auto enumerator = enumerate(vect);
    auto iter = enumerator.begin();
    iter++;
    REQUIRE(iter == enumerator.end());
    REQUIRE(iter.Index() == enumerator.end().Index());
    REQUIRE(iter.Iter() == enumerator.end().Iter());
}

TEST_CASE("move statement", "enumerate")
{
    std::vector<int> vect{ 1, 2, 3 };
    auto enumerator = enumerate(std::move(vect));
    size_t index = 0;
    size_t target = 1;

    REQUIRE(vect.empty());
    for (auto&& [i, val] : enumerator)
    {
        REQUIRE(index++ == i);
        REQUIRE(target++ == val);
    }
}

TEST_CASE("initializer_list", "enumerate")
{
    size_t index = 0;
    size_t target = 1;
    for (auto&& [i, val] : enumerate(std::initializer_list<int>({ 1, 2, 3 })))
    {
        REQUIRE(index++ == i);
        REQUIRE(target++ == val);
    }

    index = 0;
    target = 1;
    for (auto&& [i, val] : enumerate({ 1, 2, 3 }))
    {
        REQUIRE(index++ == i);
        REQUIRE(target++ == val);
    }
}
