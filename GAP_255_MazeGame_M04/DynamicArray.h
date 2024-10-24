#pragma once
         
// This is a code generation macro. It generates a class
// that encapsulates a dynamic array, with a helpful Add
// function to insert new values over time effortlessly.
// T = the data type stored in the array. Also used in the
//  name of the generated class.
// p = * if the value should be stored by pointer, or skip.
// It works by allocating extra space, then keeping track
// of where to put the next value.

#define DYNAMIC_ARRAY(T, p)                         \
class DynamicArray_##T                              \
{                                                   \
private:                                            \
    T##p* m_pArray;                                 \
    size_t m_capacity;                              \
    size_t m_occupiedSize;                          \
                                                    \
public:                                             \
    DynamicArray_##T(size_t capacity)               \
    : m_pArray{ new T##p[capacity] }                \
    , m_capacity{ capacity }                        \
    , m_occupiedSize{ 0 }                           \
    {                                               \
    }                                               \
                                                    \
    ~DynamicArray_##T()                             \
    {                                               \
        delete[] m_pArray;                          \
    }                                               \
                                                    \
    size_t GetSize() { return m_occupiedSize; }     \
                                                    \
    void Add(T##p pValue)                           \
    {                                               \
        if (m_capacity <= m_occupiedSize)           \
            return;                                 \
                                                    \
        m_pArray[m_occupiedSize] = pValue;          \
        ++m_occupiedSize;                           \
    }                                               \
                                                    \
    T##p& At(size_t index)                          \
    {                                               \
        return m_pArray[index];                     \
    }                                               \
                                                    \
    void Clear() { m_occupiedSize = 0; }            \
}