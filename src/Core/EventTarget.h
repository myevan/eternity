#pragma once

#include "Defines.h"
#include "EventHandle.h"

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
        std::unordered_map<EventHandle, Listener> m_singleListeners;
        std::unordered_map<int, std::vector<Listener>> m_groupListeners;

public:
        void Clear()
        {
                m_singleListeners.clear();
                m_groupListeners.clear();
        }

public:
        EventHandle Bind(Listener&& inListener)
        {
                EventHandle newHandle = AllocEventHandle();
                m_singleListeners.emplace(std::make_pair(newHandle, std::move(inListener)));
                return newHandle;
        }

        void Unbind(EventHandle inHandle)
        {
                m_singleListeners.erase(inHandle);
        }

public:
        void BindGroup(int group, Listener&& inListener)
        {
                m_groupListeners[group].emplace(std::move(inListener));
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
