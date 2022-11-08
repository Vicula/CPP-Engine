// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file EventHandler.h
 * @brief The event handler
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <map>
#include <typeindex>
#include <list>

#include "../Logger/Logger.h"
#include "Event.h"

class IEventCallback
{
private:
    virtual void Call(Event &e) = 0;

public:
    virtual ~IEventCallback() = default;

    void Execute(Event &e)
    {
        Call(e);
    }
};

template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback
{
private:
    typedef void (TOwner::*CallbackFunction)(TEvent &);

    TOwner *ownerInstance;
    CallbackFunction callbackFunction;

    virtual void Call(Event &e) override
    {
        std::invoke(callbackFunction, ownerInstance, static_cast<TEvent &>(e));
    }

public:
    EventCallback(TOwner *ownerInstance, CallbackFunction callbackFunction)
    {
        this->ownerInstance = ownerInstance;
        this->callbackFunction = callbackFunction;
    }

    virtual ~EventCallback() override = default;
};

typedef std::list<std::unique_ptr<IEventCallback>>
    HandlerList;

/**
 ////////////////////////////////////////////////////////////////////////////////
 /// @brief The event handler
 ////////////////////////////////////////////////////////////////////////////////
 */
class EventHandler
{
private:
    std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

public:
    EventHandler()
    {
        Logger::Log("EventHandler created");
    };

    ~EventHandler()
    {
        Logger::Log("EventHandler destroyed");
    };

    // Clears the subscribers list
    void Reset()
    {
        subscribers.clear();
    }

    /**
     /// @brief Subscribe to an event of type <T>.
     ///
     /// In our implementation, a listener subscribes to an event.
     ///
     /// @example eventHandler->SubscribeToEvent<CollisionEvent>(this, &Game::onCollision);
     ////////////////////////////////////////////////////////////////////////////////
     */
    template <typename TEvent, typename TOwner>
    void SubscribeToEvent(TOwner *ownerInstance, void (TOwner::*callbackFunction)(TEvent &))
    {
        if (!subscribers[typeid(TEvent)].get())
        {
            subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
        }
        auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(ownerInstance, callbackFunction);
        subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
    };

    /**
     /// @brief Emit an event of type <T>.
     ///
     /// In our implementation, as soon as something emits an event
     /// we go ahead and execute all the listener callback functions
     ///
     /// @example eventHandler->EmitEvent<CollisionEvent>(player, enemy);
     ////////////////////////////////////////////////////////////////////////////////
     */
    template <typename TEvent, typename... TArgs>
    void EmitEvent(TArgs &&...args)
    {
        auto handlers = subscribers[typeid(TEvent)].get();

        if (handlers)
        {
            for (auto it = handlers->begin(); it != handlers->end(); it++)
            {
                auto handler = it->get();
                TEvent event(std::forward<TArgs>(args)...);
                handler->Execute(event);
            }
        }
    };
};

#endif /* __EVENTHANDLER_H__ */