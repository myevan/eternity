#pragma once

#include <vector>
#include <deque>
#include <memory>

EL_NAMESPACE()

template<typename T>
class SharedPool
{
private:
    typedef std::shared_ptr<T> Object;

private:
    std::vector<Object> m_totalObjects;
    std::deque<Object> m_freeObjects; 

public:
    virtual ~SharedPool()
    {}

public:
    void Reserve(size_t capacity)
    {
        m_totalObjects.reserve(capacity);

        for (size_t i = m_totalObjects.size(); i <= capacity; ++i)
        {
            auto newObject = NewObject();
            m_totalObjects.push_back(newObject);
            m_freeObjects.push_back(newObject);
        }
    }

    void Reset()
    {
        m_freeObjects.clear();
        for (auto& eachObject : m_totalObjects)
        {
            m_freeObjects.push_back(eachObject);
        }
    }

public:
    Object Alloc()
    {
        if (m_freeObjects.empty())
        {
            auto newObject = NewObject();
            m_totalObjects.push_back(newObject);
            return newObject;
        }
        else
        {
            auto freeObject = m_freeObjects.front();
            m_freeObjects.pop_front();
            return freeObject;
        }
    }

    void Free(const Object& freeObject)
    {
        assert(std::find(m_totalObjects.begin(), m_totalObjects.end(), freeObject) != m_totalObjects.end());
        m_freeObjects.push_back(freeObject);
    }

protected:
    virtual std::shared_ptr<T> NewObject()
    {
        return std::make_shared<T>();
    }
};

EL_NAMESPACE_END()
