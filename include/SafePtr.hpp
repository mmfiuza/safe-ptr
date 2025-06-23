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

    // constructor
    SafePtr(const std::initializer_list<T>& il) {   
        this->_begin = new T[il.size()];
        this->_end = _begin + il.size();
        std::copy(il.begin(), il.end(), this->_begin);
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
        #ifndef SAFE_PTR_DISABLE_SELF_ASSIGNING_CHECKING
            if (this != &other) {
        #endif
                #if SAFE_PTR_DEBUG
                    --_owner_count[this->_begin];
                #endif
                this->_begin = new T[other.size()];
                std::copy(other.begin(), other.end(), this->_begin);
                #if SAFE_PTR_DEBUG
                    _owner_count[this->_begin] = 1;
                    _is_deleted[this->_begin] = false;
                #endif
        #ifndef SAFE_PTR_DISABLE_SELF_ASSIGNING_CHECKING
            }
        #endif
        return *this;
    }

    // move assignment operator
    SafePtr& operator=(SafePtr&& other) noexcept {
        #ifndef SAFE_PTR_DISABLE_SELF_ASSIGNING_CHECKING
            if (this != &other) {
        #endif
                #if SAFE_PTR_DEBUG
                    --_owner_count[this->_begin];
                #endif
                this->_begin = other._begin;
                this->_end = other._end;
                #if SAFE_PTR_DEBUG
                    ++_owner_count[this->_begin];
                #endif
        #ifndef SAFE_PTR_DISABLE_SELF_ASSIGNING_CHECKING
            }
        #endif
        return *this;
    }

    void free() const {
        #if SAFE_PTR_DEBUG
            if(_is_deleted.at(_begin) == true) {
                throw std::logic_error(
                    "the same memory pointer was freed twice"
                );
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

    T& operator[](const size_t& index) const {
        return *(_begin + index);
    }

    T& operator[](const size_t& index) {
        return const_cast<const SafePtr<T>&>(*this)[index];
    }

    T& at(const size_t& index) const {
        if (index >= this->size()) {
            throw std::out_of_range(
                "tried to access SafePtr element out of range"
            );
        }
        return *(_begin + index);
    }

    T& at(const size_t& index) {
        return const_cast<const SafePtr<T>&>(*this).at(index);
    }

    bool empty() const {
        return this->size() == 0;
    }

    void print_all(const char* const variable_name = "SafePtr::print_all") 
    const {
        std::cout << variable_name << ": {\n";
        for (const auto& t : *this) {
            std::cout << "    " << t << ",\n";
        }
        std::cout << "\033[A" << "\033[2K"; // move one line above and clear it
        std::cout << "    " << (*this)[this->size()-1] << "\n}\n";
    }

private:
    T* _begin; // points to the first element
    T* _end;   // points to the byte after the last byte of the element

    #if SAFE_PTR_DEBUG
        static std::unordered_map<T*,bool> _is_deleted;
        static std::unordered_map<T*,size_t> _owner_count;

        void _print_warning(const char* const msg) {
            std::cerr << "\033[33m" << "SafePtr warning: " << "\033[0m"
                << msg << "\n";
        }
    #endif
};

#if SAFE_PTR_DEBUG
    template<typename T>
    std::unordered_map<T*,bool> SafePtr<T>::_is_deleted;
    template<typename T>
    std::unordered_map<T*,size_t> SafePtr<T>::_owner_count;
#endif

#ifdef SAFE_PTR_NAMESPACE
    }
#endif
