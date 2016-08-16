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
        m_totalNodes.reserve(capacity);

        for (size_t i = m_totalNodes.size(); i <= capacity; ++i)
        {
            size_t newIndex = m_totalNodes.size();

            Node newNode;
            newNode.seq = 0;
            newNode.ptr = NewObject();
            m_totalNodes.push_back(newNode);
            m_freeIndices.push_back(newIndex);
        }
    }

    void Reset()
    {
        m_freeIndices.clear();
        for (size_t i = 0; i != m_totalNodes.size(); ++i)
        {
            m_totalNodes[i].seq = 0;
            m_freeIndices.push_back(i);
        }
    }

public:
    int Alloc()
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
            m_freeIndices.pop_front();

            Node& freeNode = m_totalNodes[freeIndex];
            EL_VERIFY_I(freeNode.seq == 0, freeIndex, freeNode.seq);
            freeNode.seq = newSeq;
            return NewHandle(freeIndex, newSeq);
        }
    }

    void Free(int handle)
    {
        size_t freeIndex = GetValidIndex(handle);
        EL_VERIFY_V(IsValidIndex(freeIndex), handle, freeIndex);

        Node& freeNode = m_totalNodes[freeIndex];
        EL_VERIFY_V(freeNode.seq != 0, freeIndex);
        freeNode.seq = 0;

        m_freeIndices.push_back(freeIndex);
    }

public:
    bool HasObject(int handle)
    {
        T* ptr = GetObject(handle);
        return ptr != nullptr;
    }

    T& RefObject(int handle)
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

    T* GetObject(int handle)
    {
        size_t index = GetValidIndex(handle);
        Node& node = m_totalNodes[index];
        return node.ptr;
    }

private:
    size_t GetValidIndex(int handle)
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
        static size_t s_seq = 1;
        size_t ret = s_seq;
        s_seq += 2;
        return ret;
    }

    virtual int NewHandle(size_t index, size_t seq)
    {
        return (int)(((index + 1) * 100) + (seq % 100));
    }

    virtual size_t GetQuickIndex(int handle)
    {
        return (handle / 100) - 1;
    }

    virtual size_t GetQuickSequence(int handle)
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
