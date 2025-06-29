// Copyright (c) 2025 Matheus Machado Fiuza <matheusmachadofiuza@gmail.com>

#pragma once

#include <iostream>
#include <algorithm>
#include <stdexcept>
#if SAFE_PTR_DEBUG
    #include <unordered_map>
    #include <mutex>
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
        _begin = new T[size];
        _end = _begin + size;
        #if SAFE_PTR_DEBUG
            _mtx.lock();
                _memory_id = _get_new_memory_id();
                _ref_count[_memory_id] = 1;
                _is_deleted[_memory_id] = false;
            _mtx.unlock();
        #endif
    }

    // constructor
    SafePtr(const std::initializer_list<T>& il) {   
        _begin = new T[il.size()];
        _end = _begin + il.size();
        #if SAFE_PTR_DEBUG
            _mtx.lock();
                _memory_id = _get_new_memory_id();
                _ref_count[_memory_id] = 1;
                _is_deleted[_memory_id] = false;
            _mtx.unlock();
        #endif
        std::copy(il.begin(), il.end(), this->_begin);
    }

    // destructor
    ~SafePtr() noexcept {
        #if SAFE_PTR_DEBUG
            _mtx.lock();
            --_get_ref_count_nocheck(_memory_id);
            if (_get_ref_count_nocheck(_memory_id) == 0) {
                if(!_get_is_deleted_nocheck(_memory_id)) {
                    _warning("Memory was leaked.");
                }
                _ref_count.erase(_memory_id);
                _is_deleted.erase(_memory_id);
            }
            _mtx.unlock();
        #endif
    }

    // copy constructor
    SafePtr(const SafePtr& other) {
        this->_begin = new T[other.size()];
        this->_end = this->_begin + other.size();
        #if SAFE_PTR_DEBUG
            _mtx.lock();
                this->_memory_id = _get_new_memory_id();
                _ref_count[this->_memory_id] = 1;
                _is_deleted[this->_memory_id] = false;
            _mtx.unlock();
        #endif
        std::copy(other.begin(), other.end(), this->_begin);
    }
    
    // move constructor
    SafePtr(SafePtr&& other)
    #if !SAFE_PTR_DEBUG
        noexcept
    #endif
    {
        #if SAFE_PTR_DEBUG
            _mtx.lock();
        #endif
        this->_begin = other._begin;
        this->_end = other._end;
        #if SAFE_PTR_DEBUG
            this->_memory_id = other._memory_id;
            ++_get_ref_count_nocheck(this->_memory_id);
            _mtx.unlock();
        #endif
    }

    // copy assignment operator
    SafePtr& operator=(const SafePtr& other) {
        #ifndef SAFE_PTR_DISABLE_SELF_ASSIGNING_CHECKING
            if (this != &other) {
        #endif
            #if SAFE_PTR_DEBUG
                _mtx.lock();
                --_get_ref_count_nocheck(this->_memory_id);
            #endif
            this->_begin = new T[other.size()];
            this->_end = this->_begin + other.size();
            #if SAFE_PTR_DEBUG
                this->_memory_id = _get_new_memory_id();
                _ref_count[this->_memory_id] = 1;
                _is_deleted[this->_memory_id] = false;
                _mtx.unlock();
            #endif
            std::copy(other.begin(), other.end(), this->_begin);
        #ifndef SAFE_PTR_DISABLE_SELF_ASSIGNING_CHECKING
            }
        #endif
        return *this;
    }

    // move assignment operator
    SafePtr& operator=(SafePtr&& other)
    #if !SAFE_PTR_DEBUG
        noexcept
    #endif
    {
        #ifndef SAFE_PTR_DISABLE_SELF_ASSIGNING_CHECKING
            if (this != &other) {
        #endif
            #if SAFE_PTR_DEBUG
                _mtx.lock();
                --_get_ref_count_nocheck(this->_memory_id);
            #endif
            this->_begin = other._begin;
            this->_end = other._end;
            #if SAFE_PTR_DEBUG
                this->_memory_id = other._memory_id;
                ++_get_ref_count_nocheck(this->_memory_id);
                _mtx.unlock();
            #endif
        #ifndef SAFE_PTR_DISABLE_SELF_ASSIGNING_CHECKING
            }
        #endif
        return *this;
    }

    void free() const {
        #if SAFE_PTR_DEBUG
            _mtx.lock();
            if(_get_is_deleted_nocheck(_memory_id) == true) {
                _mtx.unlock(); // unlock before it throws
                throw std::logic_error(
                    "it was tried to free the same memory pointer twice"
                );
            }
            _get_is_deleted_nocheck(_memory_id) = true;
        #endif
        delete[] _begin;
        #if SAFE_PTR_DEBUG
            _mtx.unlock();
        #endif
    }

    size_t size() const noexcept {
        return _end - _begin;
    }

    const T* begin() const noexcept {
        return _begin;
    }

    T* begin() noexcept {
        return const_cast<T*>(
            const_cast<const SafePtr<T>&>(*this).begin()
        );
    }

    const T* end() const noexcept {
        return _end;
    }

    T* end() noexcept {
        return const_cast<T*>(
            const_cast<const SafePtr<T>&>(*this).end()
        );
    }

    const T& operator[](const size_t& index) const noexcept {
        return *(_begin + index);
    }

    T& operator[](const size_t& index) noexcept {
        return const_cast<T&>(
            const_cast<const SafePtr<T>&>(*this)[index]
        );
    }

    const T& at(const size_t& index) const {
        if (index >= this->size()) {
            throw std::out_of_range(
                "tried to access SafePtr element out of range"
            );
        }
        return *(_begin + index);
    }

    T& at(const size_t& index) {
        return const_cast<T&>(
            const_cast<const SafePtr<T>&>(*this).at(index)
        );
    }

    bool empty() const noexcept {
        return this->size() == 0;
    }

    const T* data() const noexcept {
        return _begin;
    }

    T* data() noexcept {
        return const_cast<T*>(
            const_cast<const SafePtr<T>&>(*this).data()
        );
    }

    const T& front() const noexcept {
        return *(this->_begin);
    }

    T& front() noexcept {
        return const_cast<T&> (
            const_cast<const SafePtr<T>&>(*this).front()
        );
    }

    const T& back() const noexcept {
        return *(this->_end-1);
    }

    T& back() noexcept {
        return const_cast<T&>(
            const_cast<const SafePtr<T>&>(*this).back()
        );
    }

    void fill(const T& value) {
        for (auto& p : *this) {
            p = value;
        }
    }

    void print_all(const char* const variable_name = "SafePtr::print_all") 
    const {
        std::cout << variable_name << ": {\n";
        if (!this->empty()) {
            for (const auto& t : *this) {
                std::cout << "    " << t << ",\n";
            }
            std::cout << "\033[A" << "\033[2K"; // move to line above and clear
            std::cout << "    " << this->back() << "\n";
        }
        std::cout << "}\n";
    }

private:
    T* _begin; // points to the first element
    T* _end;   // points to the byte after the last byte of the element

    #if SAFE_PTR_DEBUG
        size_t _memory_id;
        static size_t _next_available_memory_id;
        static std::unordered_map<size_t,size_t> _ref_count;
        static std::unordered_map<size_t,bool> _is_deleted;
        static std::mutex _mtx;

        size_t& _get_new_memory_id() const noexcept {
            ++_next_available_memory_id;
            return _next_available_memory_id;
        }

        size_t& _get_ref_count_nocheck(const size_t& id)
        const noexcept {
            typename std::unordered_map<size_t,size_t>::iterator it = 
                _ref_count.find(id);
            return it->second;
        }

        bool& _get_is_deleted_nocheck(const size_t& id)
        const noexcept {
            typename std::unordered_map<size_t,bool>::iterator it =
                _is_deleted.find(id);
            return it->second;
        }

        void _warning(const char* const msg) const {
            std::cerr << "\033[33m" << "SafePtr warning: " << "\033[0m"
                << msg << "\n";
        }

    #endif
};

#if SAFE_PTR_DEBUG
    template<typename T>
    std::unordered_map<size_t,size_t> SafePtr<T>::_ref_count;
    template<typename T>
    std::unordered_map<size_t,bool> SafePtr<T>::_is_deleted;

    template<typename T> size_t SafePtr<T>::_next_available_memory_id = 0;
    
    template<typename T> std::mutex SafePtr<T>::_mtx;
#endif

#ifdef SAFE_PTR_NAMESPACE
    }
#endif
