// Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

#pragma once

#include "assert.hpp"
#include <vector>
#include <array>

void test_view()
{
    // general usage
    std::vector<int> vec = {1, 2, 3};
    auto vec_view = fz::SafePtr<int>::make_view(vec.data(), vec.size());
    vec_view[0] = 4;
    vec_view[1] = 5;
    vec_view[2] = 6;
    ASSERT_EQ(vec[0], vec_view[0]);
    ASSERT_EQ(vec[1], vec_view[1]);
    ASSERT_EQ(vec[2], vec_view[2]);
    #ifdef SAFE_PTR_DEBUG
        ASSERT_THROWS(vec_view.free());
    #endif

    // copy constructor
    auto vec_cp = vec_view;
    ASSERT_EQ(vec_cp[0], vec_view[0]);
    ASSERT_EQ(vec_cp[1], vec_view[1]);
    ASSERT_EQ(vec_cp[2], vec_view[2]);
    ASSERT_DIFF(vec_view.data(), vec_cp.data());
    ASSERT_DIFF(vec_view.begin(), vec_cp.begin());
    ASSERT_DIFF(vec_view.end(), vec_cp.end());
    vec_cp.free();

    // move constructor
    auto vec_mv = std::move(vec_view);
    ASSERT_EQ(vec_mv[0], 4);
    ASSERT_EQ(vec_mv[1], 5);
    ASSERT_EQ(vec_mv[2], 6);
    #ifdef SAFE_PTR_DEBUG
        ASSERT_THROWS(vec_mv.free());
    #endif

    // copy assignment operator
    fz::SafePtr<int> vec_cpop = {7, 8, 9};
    vec_cpop.free();
    vec_cpop = vec_view;
    ASSERT_EQ(vec_cpop[0], vec_view[0]);
    ASSERT_EQ(vec_cpop[1], vec_view[1]);
    ASSERT_EQ(vec_cpop[2], vec_view[2]);
    ASSERT_DIFF(vec_view.data(), vec_cpop.data());
    ASSERT_DIFF(vec_view.begin(), vec_cpop.begin());
    ASSERT_DIFF(vec_view.end(), vec_cpop.end());
    vec_cpop.free();
    std::array<int,3> arr1 = {1, 2, 3};
    std::array<int,3> arr2 = {4, 5, 6};
    auto arr1_view = fz::SafePtr<int>::make_view(arr1.data(), arr1.size());
    auto arr2_view = fz::SafePtr<int>::make_view(arr2.data(), arr2.size());
    arr2_view = arr1_view;
    ASSERT_EQ(arr1_view[0], arr2_view[0]);
    ASSERT_EQ(arr1_view[1], arr2_view[1]);
    ASSERT_EQ(arr1_view[2], arr2_view[2]);
    ASSERT_DIFF(arr1_view.data(), arr2_view.data());
    ASSERT_DIFF(arr1_view.begin(), arr2_view.begin());
    ASSERT_DIFF(arr1_view.end(), arr2_view.end());
    arr2_view.free();

    // move assignment operator
    fz::SafePtr<int> vec_mvop = {7, 8, 9};
    vec_mvop.free();
    vec_mvop = std::move(vec_view);
    ASSERT_EQ(vec_mvop[0], vec_view[0]);
    ASSERT_EQ(vec_mvop[1], vec_view[1]);
    ASSERT_EQ(vec_mvop[2], vec_view[2]);
    ASSERT_EQ(vec_view.data(), vec_mvop.data());
    ASSERT_EQ(vec_view.begin(), vec_mvop.begin());
    ASSERT_EQ(vec_view.end(), vec_mvop.end());
    #ifdef SAFE_PTR_DEBUG
        ASSERT_THROWS(vec_mvop.free());
    #endif
    std::array<int,3> arr3 = {1, 2, 3};
    std::array<int,3> arr4 = {4, 5, 6};
    auto arr3_view = fz::SafePtr<int>::make_view(arr3.data(), arr3.size());
    auto arr4_view = fz::SafePtr<int>::make_view(arr4.data(), arr4.size());
    arr4_view = std::move(arr3_view);
    ASSERT_EQ(arr3_view[0], arr4_view[0]);
    ASSERT_EQ(arr3_view[1], arr4_view[1]);
    ASSERT_EQ(arr3_view[2], arr4_view[2]);
    ASSERT_EQ(arr3_view.data(), arr4_view.data());
    ASSERT_EQ(arr3_view.begin(), arr4_view.begin());
    ASSERT_EQ(arr3_view.end(), arr4_view.end());
}