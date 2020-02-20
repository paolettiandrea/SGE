#ifndef NON_GRAVITAR_ANIMATION_HPP
#define NON_GRAVITAR_ANIMATION_HPP


#include <SGE/utils/interpolation/Interpolator.hpp>
#include <SGE/utils/events/Events.hpp>

namespace sge {
    class Animation {
    public:
        Animation(Interpolator *interpolator, float from_val, float to_val, float duration = 1.0);
        virtual ~Animation();

        void set_from_val(float val);
        void set_to_val(float val);

        void set_duration(float seconds);

        void start(bool reset = true);
        void stop();


        float get_fraction();

        float step(float delta_time);

        float get_val();

        float get_timer();

        utils::event::Event on_animation_ended;

        bool is_done();

        bool is_active();

        float get_from_val();
        float get_to_val();


    private:
        float m_elapsed_seconds = 0;
        float m_duration;
        float m_from_val, m_to_val;
        bool m_active = false;

        Interpolator* m_interpolator;
    };
}



#endif //NON_GRAVITAR_ANIMATION_HPP
