#pragma once

#include "Sequence32.h"

#include <functional>
#include <unordered_map>
#include <vector>

EL_NAMESPACE()

template<typename T>
class EventTarget
{
public:
        typedef std::function<void(const T&)> Listener;

private:        
        std::unordered_map<int, Listener> m_singleListeners;
        std::unordered_map<int, std::vector<Listener>> m_groupListeners;

public:
        void Clear()
        {
                m_singleListeners.clear();
                m_groupListeners.clear();
        }

public:
        int Bind(Listener&& listener)
        {
                int handle = Sequence32::Get().Alloc();
                m_singleListeners.emplace(std::make_pair(handle, std::move(listener)));
                return handle;
        }

        void Unbind(int handle)
        {
                m_singleListeners.erase(handle);
        }

public:
        void BindGroup(int group, Listener&& listener)
        {
                m_groupListeners[group].emplace(std::move(listener));
        }

        void UnbindGroup(int group)
        {
                m_groupListeners.erase(group);
        }

public:
        void Broadcast(const T& data)
        {
                if (!m_singleListeners.empty())
                {
                        for (auto& eachIter : m_singleListeners)
                        {
                                eachIter.second(data);
                        }
                }

                if (!m_groupListeners.empty())
                {
                        for (auto& groupIter : m_groupListeners)
                        {
                                auto& group = groupIter.second;
                                for (auto& memberIter : group)
                                {
                                        memberIter(data);
                                }
                        }
                }
        }
};

EL_NAMESPACE_END()
