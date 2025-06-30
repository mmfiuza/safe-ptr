// Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

#pragma once

#include "assert.hpp"
#include <thread>
#include <vector>

void test_ref_count()
{
    size_t thread_count = 1000;

    SafePtr<float> a = {1,2,3,4}; 
    std::vector<std::thread> t0;
    for (size_t i=0; i!=thread_count; ++i) {
        t0.push_back(std::thread([&](){
            auto x = std::move(a);
        }));
    }
    for (size_t i=0; i!=thread_count; ++i) {
        t0[i].join();
    }
    a.free();
    
    
    SafePtr<float> b = {1,2,3,4};
    std::vector<std::thread> t1;
    for (size_t i=0; i!=thread_count; ++i) {
        t1.push_back(std::thread([&](){
            SafePtr<float> x = {5,4,3,2,1};
            SafePtr<float> y = {7,8,9};
            x.free();
            x = b;
            x.free();
            x = std::move(y);
            x.free();
            auto z = b;
            z.free();
        }));
    }
    for (size_t i=0; i!=thread_count; ++i) {
        t1[i].join();
    }  
    b.free();

}