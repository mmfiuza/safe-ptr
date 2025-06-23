// Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

#pragma once

#include <iostream>
#include <algorithm>
#include <stdexcept>
#if SAFE_PTR_DEBUG
    #include <unordered_map>
#endif

#ifdef SAFE_PTR_NAMESPACE
    namespace SAFE_PTR_NAMESPACE {
#endif

template<typename T>
class SafePtr
{
    public:
        // constructor
        SafePtr(const size_t& size) {
            this->_begin = new T[size];
            this->_end = _begin + size;
            #if SAFE_PTR_DEBUG
                _owner_count[this->_begin] = 1;
                _is_deleted[this->_begin] = false;
            #endif
        }

        // destructor
        ~SafePtr() {
            #if SAFE_PTR_DEBUG
                --_owner_count.at(_begin);
                if (_owner_count.at(_begin)==0 && !_is_deleted.at(_begin)) {
                    _print_warning("Memory was leaked.");
                }
            #endif
        }

        // copy constructor
        SafePtr(const SafePtr& other) {
            this->_begin = new T[other.size()];
            this->_end = this->_begin + other.size();
            std::copy(other.begin(), other.end(), this->_begin);
            #if SAFE_PTR_DEBUG
                _owner_count[this->_begin] = 1;
                _is_deleted[this->_begin] = false;
            #endif
        }
        
        // move constructor
        SafePtr(SafePtr&& other) noexcept {
            this->_begin = other._begin;
            this->_end = other._end;
            #if SAFE_PTR_DEBUG
                ++_owner_count[this->_begin];
            #endif
        }

        // copy assignment operator
        SafePtr& operator=(const SafePtr& other) {
            if (this != &other) {
                #if SAFE_PTR_DEBUG
                    --_owner_count[this->_begin];
                #endif
                this->_begin = new T[other.size()];
                std::copy(other.begin(), other.end(), this->_begin);
                #if SAFE_PTR_DEBUG
                    _owner_count[this->_begin] = 1;
                    _is_deleted[this->_begin] = false;
                #endif
            }
            return *this;
        }

        // move assignment operator
        SafePtr& operator=(SafePtr&& other) noexcept {
            if (this != &other) {
                #if SAFE_PTR_DEBUG
                    --_owner_count[this->_begin];
                #endif
                this->_begin = other._begin;
                this->_end = other._end;
                #if SAFE_PTR_DEBUG
                    ++_owner_count[this->_begin];
                #endif
            }
            return *this;
        }

        void free() {
            #if SAFE_PTR_DEBUG
                if(_is_deleted.at(_begin) == true) {
                    throw std::logic_error("the same memory pointer was freed twice");
                }
                _is_deleted.at(_begin) = true;
            #endif
            delete[] _begin;
        }

        size_t size() const {
            return _end - _begin;
        }

        T* begin() const {
            return _begin;
        }

        T* end() const {
            return _end;
        }

        T& operator[](const size_t& index) {
            return *(_begin + index);
        }

        void print_all() const {
            std::cout << "SafePtr::print_all:\n";
            for (auto& t : *this) {
                std::cout << "    " << t << "\n";
            }
        }

    private:
        T* _begin; // points to the first element
        T* _end;   // points to the byte after the last byte of the element

        #if SAFE_PTR_DEBUG
            static std::unordered_map<T*,bool> _is_deleted; // TODO: check if this is redundant
            static std::unordered_map<T*,size_t> _owner_count;

            void _print_warning(const char* const msg) {
                std::cerr << "\033[33m" << "SafePtr warning: " << "\033[0m" << msg << "\n";
            }
        #endif
};

#if SAFE_PTR_DEBUG
    template<typename T> std::unordered_map<T*,bool> SafePtr<T>::_is_deleted;
    template<typename T> std::unordered_map<T*,size_t> SafePtr<T>::_owner_count;
#endif

#ifdef SAFE_PTR_NAMESPACE
    }
#endif
