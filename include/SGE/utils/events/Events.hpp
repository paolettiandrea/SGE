//
// Created by andrea on 5/8/19.
//

#ifndef FACTORY_EXPERIMENTS_EVENTS_HPP
#define FACTORY_EXPERIMENTS_EVENTS_HPP

#include <vector>
#include <memory>
#include "EventHandler.hpp"


namespace utils {
    namespace event {
        /*!
         * \brief An object modeling an event that can have an arbitrary number of EventHandler subscribers and can notify them at the occurrence.
         * \see http://www.dannyb.me/posts/2014/02/creating_event_system_c++/
         */
        class Event {
            std::vector<EventHandler*> subscribers;

            void notifyHandlers();
        public:
            /*!
             * \brief Adds a EventHandler as subscriber of the event.
             */
            void addHandler(const EventHandler &handler);
            /*!
             * \brief Removes the handler from the subscriber list
             */
            void removeHandler(const EventHandler &handler);
            /*!
             * \brief Used to notify every subscriber, causes the call of every function in every EventHandler subscriber.
             */
            void operator()();
            /*!
             * \brief Equivalent to addHandler().
             */
            Event &operator+=(const EventHandler &handler);
            /*!
             * \brief Equivalent to addHandler().
             */
            Event &operator+=(const EventHandler::Func &handler);
            /*!
             * \brief Equivalent to removeHandler().
             */
            Event &operator-=(const EventHandler &handler);
            /*!
             * \brief Returns the total number of Handlers that are subscribed to this event in this moment.
             */
            unsigned long totalHandlers() { return this->subscribers.size(); }
        };
    }
}


/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

class Events {

};


#endif //FACTORY_EXPERIMENTS_EVENTS_HPP