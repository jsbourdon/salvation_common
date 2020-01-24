#pragma once

#include "Salvation_Common/Memory/ThreadHeapAllocator.h"

namespace salvation
{
    namespace memory
    {
        template<typename T>
        struct ThreadHeapSmartPointer
        {
            ThreadHeapSmartPointer(void *pPtr) : m_pPtr(static_cast<T*>(pPtr)) {}
            ThreadHeapSmartPointer(const ThreadHeapSmartPointer& other) = delete;
            ThreadHeapSmartPointer(ThreadHeapSmartPointer&& other) { m_pPtr = other.m_pPtr; other.m_pPtr = nullptr; }
            ~ThreadHeapSmartPointer() { if (m_pPtr) ThreadHeapAllocator::Release(m_pPtr); }

            inline operator T*() { return m_pPtr; }
            inline T& operator[](size_t index) { return m_pPtr[index]; }
            inline T* operator+(size_t offset) { return m_pPtr + offset; }
            inline T* operator->() { return m_pPtr; }
            inline T operator*() { return *m_pPtr; }

        private:
            T *m_pPtr;
        };

        using str_smart_ptr = ThreadHeapSmartPointer<char>;
    }
}