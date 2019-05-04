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
            /*!
             * \brief Constructor for a Loggable
             * \param name The name that will be displayed in the id box on logs
             */
            Loggable(const std::string &name);

            virtual ~Loggable();

            /*!
             * @return A string that will constitute the header of the logged string, it should contain a bunch of relevant information about the object logging the string
             */
            virtual std::string get_logger_header();
            /*!
             * \brief Gets the log_id of this Loggable
             * \return The log_id
             */
            virtual const std::string &get_log_id() const;

            /*!
             * \brief Sets the log_id of this Loggable to a new string
             * \param name The new string that the id should change to
             */
            void set_log_id(const std::string &name);

        private:
            std::string log_id = "placeholder_id";



        };
    }
}

#endif //SGE_ILOGGABLE_HPP

