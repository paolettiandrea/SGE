#ifndef FACTORY_EXPERIMENTS_ILOGICCALLBACKS_HPP
#define FACTORY_EXPERIMENTS_ILOGICCALLBACKS_HPP

namespace sge {
    /*!
 * \brief Interface that contains all the callback that a Logic object can have.
 */
    struct ILogicCallbacks {

        virtual void on_start() = 0;
        virtual void on_destruction() = 0;

        virtual void on_update() = 0;
        virtual void on_fixed_update() = 0;

    };
}


#endif //FACTORY_EXPERIMENTS_ILOGICCALLBACKS_HPP
