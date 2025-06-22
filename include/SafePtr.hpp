// Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

#pragma once

#include <iostream>
#if SAFE_PTR_DEBUG
    #include <unordered_map>
#endif

template<typename T>
class SafePtr // TODO: apply rule of five
{
    public:
        // constructor
        SafePtr(const size_t& size) {
            this->ptr_begin = new T[size];
            if (this->ptr_begin == nullptr)
                std::cout << "\"new\" operator failed to allocate memory.\n";
            this->ptr_end = ptr_begin + size;
            #if SAFE_PTR_DEBUG
                owner_count[ptr_begin] = 1;
                is_deleted[ptr_begin] = false;
            #endif
        }

        // destructor
        ~SafePtr() {
            #if SAFE_PTR_DEBUG
                --owner_count.at(ptr_begin);
                if (owner_count.at(ptr_begin)==0 && !is_deleted.at(ptr_begin))
                    log_system.warning("Memory was leaked.");
            #endif
        }

        // copy constructor
        SafePtr(const SafePtr& other) {
            this->ptr_begin = new T[other.size()];
            this->ptr_end = this->ptr_begin + other.size();
            for (
                T *it_this=this->ptr_begin, *it_other=other.ptr_begin;
                it_this != this->ptr_end;
                ++it_this, ++it_other
            ) {
                *it_this = *it_other; // calls the copy assignment operator of each T
            }
            #if SAFE_PTR_DEBUG
                owner_count[this->ptr_begin] = 1;
                is_deleted[ptr_begin] = false;
            #endif
        }
        
        // move constructor
        SafePtr(SafePtr&& other) noexcept {
            this->ptr_begin = other.ptr_begin;
            this->ptr_end = other.ptr_end;
            other.ptr_begin = nullptr;
            other.ptr_end = nullptr; // TODO: rethink if this is needed
        }

        void free() {
            #if SAFE_PTR_DEBUG
                if(is_deleted.at(ptr_begin)==true)
                    log_system.error("The same memory was freed twice.");
                is_deleted.at(ptr_begin) = true;
            #endif
            delete[] ptr_begin;
        }

        size_t size() const {
            return ptr_end - ptr_begin;
        }

        T* begin() const {
            return ptr_begin;
        }

        T* end() const {
            return ptr_end;
        }

        T& operator[](const size_t& index) {
            return *(ptr_begin + index);
        }

    private:
        T* ptr_begin; // points to the first element
        T* ptr_end;   // points to the byte after the last byte of the element
        #if SAFE_PTR_DEBUG
            static std::unordered_map<T*,bool> is_deleted;
            static std::unordered_map<T*,size_t> owner_count;
        #endif
};
