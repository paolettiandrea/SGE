//
// Created by andrea on 4/9/19.
//


#ifndef SGE_LOGGABLE_HPP
#define SGE_LOGGABLE_HPP

#include <string>
#include "Log.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/


namespace utils {
    namespace log {
        /*!
        * Object that is loggable, which means that provides some information
        * about himself that the Logger prints with it's log string.
        */
        class Loggable {
        public:
            Loggable(const std::string &name);

            virtual ~Loggable();

            /*!
             * @return A string that will constitute the header of the logged string, it should contain a bunch of relevant information about the object logging the string
             */
            virtual std::string get_logger_header();

            virtual const std::string &get_log_id() const;

            void set_log_id(const std::string &name);

        private:
            std::string log_id = "placeholder_id";



        };
    }
}

#endif //SGE_ILOGGABLE_HPP

