//
// Created by andrea on 5/8/19.
//

#include "SGE/utils/events/Events.hpp"

using  namespace utils::event;

using std::vector;
using std::unique_ptr;


void Event::notifyHandlers() {
    auto func = this->subscribers.begin();
    for(; func != this->subscribers.end(); ++func) {
        if(*func != nullptr && (*func)->get_id() != 0) {
            (*(*func))();
        }
    }
}

void Event::addHandler(const EventHandler &handler) {
    this->subscribers.push_back((new EventHandler{handler}));
}

void Event::removeHandler(const EventHandler &handler) {
    bool found = false;
    auto to_remove = this->subscribers.begin();
    for(; to_remove != this->subscribers.end(); ++to_remove) {
        if(*(*to_remove) == handler) {
            this->subscribers.erase(to_remove);
            found = true;
            break;
        }
    }
    if (!found) std::cerr << "Tried to remove an EventHandler from an event but it wasn't found";
}

void Event::operator()() {
    this->notifyHandlers();
}

Event &Event::operator+=(const EventHandler &handler) {
    this->addHandler(handler);

    return *this;
}

Event &Event::operator+=(const EventHandler::Func &handler) {
    this->addHandler(EventHandler{handler});

    return *this;
}

Event &Event::operator-=(const EventHandler &handler) {
    this->removeHandler(handler);

    return *this;
}
