#ifndef FACTORY_EXPERIMENTS_ILOGICCALLBACKS_HPP
#define FACTORY_EXPERIMENTS_ILOGICCALLBACKS_HPP

struct ILogicCallbacks {

    virtual void on_start() = 0;
    virtual void on_destruction() = 0;

    virtual void on_update() = 0;
    virtual void on_fixed_update() = 0;

};
#endif //FACTORY_EXPERIMENTS_ILOGICCALLBACKS_HPP
