//
// Created by andrea on 5/8/19.
//

#include "SGE/utils/events/EventHandler.hpp"

using namespace utils::event;

int EventHandler::id_counter = 0;

void EventHandler::operator()() {
    this->_func();
}

void EventHandler::operator=(const Func &func) {
    if(this->_func == nullptr) {
        this->_func = func;
        this->id = ++EventHandler::id_counter;
    } else {
        std::cerr << "You shouldn't set the func of an event handler a second time!" << std::endl;
        exit(1);
    }
}

bool EventHandler::operator==(const EventHandler &del) {
    return this->id == del.id;
}
bool EventHandler::operator!=(nullptr_t) {
    return this->_func != nullptr;
}

int EventHandler::get_id() const {
    return id;
}