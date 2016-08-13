#pragma once

#include "Defines.h"
#include "Types.h"

#include <vector>
#include <deque>

EL_NAMESPACE()

template<typename T>
class HandlePool
{
private:
    struct Node
    {
        size_t seq;
        T* ptr;
    };

private:
    std::vector<Node>  m_totalNodes;
    std::deque<size_t> m_freeIndices; 

public:
    ~HandlePool()
    {
        for (auto& eachNode : m_totalNodes)
        {
            delete eachNode.ptr;
        }
    }

public:
    void Reserve(size_t capacity)
    {
        for (size_t i = 0; i != capacity; ++i)
        {
            int_t handle = Alloc();
            size_t index = GetQuickIndex(handle);
            m_freeIndices.push_back(index);
        }
    }

    void Reset()
    {
        m_freeIndices.clear();
        for (size_t i = 0; i != m_totalNodes.size(); ++i)
        {
            m_freeIndices.push_back(i);
        }
    }

public:
    int_t Alloc()
    {
        size_t newSeq = NewSequence();

        if (m_freeIndices.empty())
        {
            size_t newIndex = m_totalNodes.size();

            Node newNode;
            newNode.seq = newSeq;
            newNode.ptr = NewObject();
            m_totalNodes.push_back(newNode);

            return NewHandle(newIndex, newSeq);
        }
        else
        {
            size_t freeIndex = m_freeIndices.front();
            Node& freeNode = m_totalNodes[freeIndex];
            freeNode.seq = newSeq;
            return NewHandle(freeIndex, newSeq);
        }
    }

    void Free(int_t handle)
    {
        size_t index = GetValidIndex(handle);
        EL_VERIFY_V(IsValidIndex(index), handle, index);

        m_freeIndices.push_back(index);
    }

public:
    bool IsObject(int_t handle)
    {
        T* ptr = GetObject(handle);
        return ptr != nullptr;
    }

    T& RefObject(int_t handle)
    {
        T* ptr = GetObject(handle);
        if (ptr == nullptr)
        {
            return RefDefaultObject();
        }
        else
        {
            return *ptr;
        }
    }

    T* GetObject(int_t handle)
    {
        size_t index = GetValidIndex(handle);
        Node& node = m_totalNodes[index];
        return node.ptr;
    }

private:
    size_t GetValidIndex(int_t handle)
    {
        size_t size = m_totalNodes.size();
        size_t index = GetQuickIndex(handle);
        EL_VERIFY_U(index < size, index, size);

        size_t seq = GetQuickSequence(handle);
        Node& node = m_totalNodes[index];
        EL_VERIFY_U(seq == node.seq, index, seq, node.seq);

        return index;
    }

    bool IsValidIndex(size_t index)
    {
        return index < m_totalNodes.size();
    }

protected:
    virtual T* NewObject()
    {
        return new T();
    }

    virtual size_t NewSequence()
    {
        static size_t s_seq = 0;
        return s_seq++;
    }

    virtual int_t NewHandle(size_t index, size_t seq)
    {
        return (int_t)(index * 100) + (seq % 100);
    }

    virtual size_t GetQuickIndex(int_t handle)
    {
        return handle / 100;
    }

    virtual size_t GetQuickSequence(int_t handle)
    {
        return handle % 100;
    }

    virtual T& RefDefaultObject()
    {
        static T s_defaultObject;
        return s_defaultObject;
    }
};

EL_NAMESPACE_END()
