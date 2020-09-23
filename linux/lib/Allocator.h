#pragma once

#include <atomic>
#include <memory>

std::atomic_int mem_size{0};

template <typename T>
class Allocator : public std::allocator<T>
{
private:
    using Base = std::allocator<T>;
    using Ptr  = typename std::allocator_traits<Base>::pointer;
    using SizeType = typename std::allocator_traits<Base>::size_type;
public:
    Ptr allocate(size_t n)
    {
        mem_size.fetch_add(n * sizeof(T));
        return Base::allocate(n);
    }

    void deallocate(Ptr p, SizeType n)
    {
        mem_size.fetch_sub(n * sizeof(T));
        Base::deallocate(p, n);
    }
}