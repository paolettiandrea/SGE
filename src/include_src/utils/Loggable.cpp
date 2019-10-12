#include "Loggable.hpp"
#include "Time.hpp"

using utils::log::Loggable;

std::string Loggable::get_logger_header() {
    std::stringstream ss;
    ss << this;


    return "T:[" + std::string(time::get_hi_res_time_stamp()) + "]\t A:[" + ss.str() + "]";
}

Loggable::Loggable(const std::string &name) {
    this->log_id = name;
}

const std::string &Loggable::get_log_id() const {
    return log_id;
}

void Loggable::set_log_id(const std::string &name) {
    this->log_id = name;
}

utils::log::Loggable::~Loggable() {

}
