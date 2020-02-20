#include "SGE/utils/events/Events.hpp"

using  namespace utils::event;

using std::vector;
using std::unique_ptr;


void Event::notifyHandlers() {
    auto func = this->subscribers.begin();
    for(; func != this->subscribers.end(); ++func) {
        if(func->is_valid() && (*func).get_id() != 0) {
            (*func)();
        }
    }
}

int Event::addHandler(const EventHandler &handler) {
    this->subscribers.emplace_back(handler);
    return handler.get_id();
}

void Event::removeHandler(const EventHandler &handler_to_remove) {
    bool found = false;
    auto target = this->subscribers.begin();
    for(; target != this->subscribers.end(); ++target) {
        if((*target) == handler_to_remove) {
            this->subscribers.erase(target);
            found = true;
            break;
        }
    }

    if (EVENTS_WARNING_ON_MISSED_REMOVAL && !found) {
        std::cerr << "Tried to remove an EventHandler from an event but it wasn't found\n";
    }
}

void Event::removeHandler(int handler_id) {
    bool found = false;
    auto target = this->subscribers.begin();
    for(; target != this->subscribers.end(); ++target) {
        if((*target).get_id() == handler_id) {
            this->subscribers.erase(target);
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

void Event::clearSubscribers() {
    this->subscribers.clear();
}

