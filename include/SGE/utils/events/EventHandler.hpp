//
// Created by andrea on 5/8/19.
//

#ifndef SGE_EVENTHANDLER_HPP
#define SGE_EVENTHANDLER_HPP


#include <functional>
#include <iostream>


namespace utils {
    namespace event {

/*!
* \brief Handler that wraps around a function and can subscribe to multipe Event in order to have the function called when the event is notified.
*/
        class EventHandler {
        public:
            using Func = std::function<void()>;

        private:
            /*!
             * Just a static counter used to assign unique ids to the handlers.
             */
            static int id_counter;
            /*!
             * The function stored internally, will be called when an event this handler is subscribed to will be called.
             */
            Func _func;
            /*!
             * \brief The unique id of the handler, it's 0 until a function is assigned to the handler
             */
            int id;

        public:

            EventHandler() : id{0} {}

            EventHandler(const EventHandler& that) {
                this->_func = that._func;
                this->id = that.id;
            }

            explicit EventHandler(const Func &func) : _func{func} {
                this->id = ++EventHandler::id_counter;
            }

            /*!
 * \brief Returns the unique id of this EventHandler, it's 0 until a function is assigned to it.
 */
            int get_id() const;

            /*!
             * \brief Used to call the contained function.
             */
            void operator()();
            /*!
             * Used to assign to the handler a function, it's a necessary step before subscription.
             */
            void operator=(const Func &func);
            /*!
             * \brief Checks if the two EventHandlers have the same id
             */
            bool operator==(const EventHandler &del);

            bool is_valid();
        };
    }
}



/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/



#endif //SGE_EVENTHANDLER_HPP
