// Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

#pragma once

#include "assert.hpp"

void test_rule_of_5()
{
    // regular constructors //
    SafePtr<double> ptr0(0);
    SafePtr<double> ptr1(5);
    SafePtr<double> ptr2(5);
    const SafePtr<double> ptr3 = {1.0, 1.2, 1.5};
    std::initializer_list<double> il1 = {1.5, 7.3, 9.7, 1.4}; 
    SafePtr<double> ptr4 = il1;
    const std::initializer_list<double> il2 = {1.4, 1.4, 8.7, 5.3}; 
    SafePtr<double> ptr5 = il2;
    std::initializer_list<double> il3 = {9.9, 1.7, 6.7, 8.4}; 
    const SafePtr<double> ptr6 = il3;


    // copy constructor //
    auto ptr7 = ptr0;
    const SafePtr<double> ptr8 = ptr4;
    ASSERT_EQ(ptr8[0], ptr4[0]);
    ASSERT_EQ(ptr8[1], ptr4[1]);
    ASSERT_EQ(ptr8[2], ptr4[2]);
    ASSERT_EQ(ptr8[3], ptr4[3]);
    ASSERT_DIFF(ptr8.data(), ptr4.data());
    ASSERT_DIFF(ptr8.begin(), ptr4.begin());
    ASSERT_DIFF(ptr8.end(), ptr4.end());

    
    // move constructor //
    const SafePtr<double> ptr9 = std::move(ptr4);
    ASSERT_EQ(ptr9[0], ptr4[0]);
    ASSERT_EQ(ptr9[1], ptr4[1]);
    ASSERT_EQ(ptr9[2], ptr4[2]);
    ASSERT_EQ(ptr9[3], ptr4[3]);
    ASSERT_EQ(ptr9.data(), ptr4.data());
    ASSERT_EQ(ptr9.begin(), ptr4.begin());
    ASSERT_EQ(ptr9.end(), ptr4.end());

    // copy assignment operator
    ptr2.free();
    ptr2 = ptr6;
    ASSERT_EQ(ptr2[0], ptr6[0]);
    ASSERT_EQ(ptr2[1], ptr6[1]);
    ASSERT_EQ(ptr2[2], ptr6[2]);
    ASSERT_EQ(ptr2[3], ptr6[3]);
    ASSERT_DIFF(ptr2.data(), ptr6.data());
    ASSERT_DIFF(ptr2.begin(), ptr6.begin());
    ASSERT_DIFF(ptr2.end(), ptr6.end());


    // move assignment operator
    ptr1.free();
    ptr1 = std::move(ptr5);
    ASSERT_EQ(ptr1[0], ptr5[0]);
    ASSERT_EQ(ptr1[1], ptr5[1]);
    ASSERT_EQ(ptr1[2], ptr5[2]);
    ASSERT_EQ(ptr1[3], ptr5[3]);
    ASSERT_EQ(ptr1.data(), ptr5.data());
    ASSERT_EQ(ptr1.begin(), ptr5.begin());
    ASSERT_EQ(ptr1.end(), ptr5.end());


    // free memory //
    ptr0.free();
    ptr1.free();
    ptr2.free();
    ptr3.free();
    ptr4.free();
    #if SAFE_PTR_DEBUG
        ASSERT_THROWS(ptr5.free());
    #endif
    ptr6.free();
    ptr7.free();
    ptr8.free();
    #if SAFE_PTR_DEBUG
        ASSERT_THROWS(ptr9.free());
    #endif
}
