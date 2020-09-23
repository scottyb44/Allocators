#pragma once

#include <atomic>
#include <memory>

std::atomic_int global_memory_used{0};

template <typename T>
class Allocator : public std::allocator<T>
{
private:
    using Base = std::allocator<T>;
    using Ptr  = typename std::allocator_traits<Base>::pointer;
    using SizeType = typename std::allocator_traits<Base>::size_type;
public:
    Allocator() = default;

    // This and the bind struct allow the allocator to be able to rebind
    template <typename U>
    Allocator(const Allocator<U>& other)
        : Base(other)
    {
    }
    template <typename U>
    struct rebind
    {
        using other = Allocator<U>;
    };

    Ptr allocate(size_t n)
    {
        global_memory_used.fetch_add(n * sizeof(T));
        return Base::allocate(n);
    }

    void deallocate(Ptr p, SizeType n)
    {
        std::cout << "deallocating: " << (n * sizeof(T)) << " bytes from location: " << p << std::endl;
        global_memory_used.fetch_sub(n * sizeof(T));
        Base::deallocate(p, n);
    }
};
