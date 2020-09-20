#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Touch
{
    public:
        struct Configuration
        {
            uint8_t Histeresis;
            struct
            {
                uint8_t PressedMax;
                uint8_t ReleasedMax;
            } Time;
        };

        explicit Touch (Configuration v_config) : config (v_config) { }
        virtual ~Touch () = default;

        virtual void Process    (void) = 0;
        bool         IsPressed  (void) { return (event () == EState::ePressed ) ? true : false; }
        bool         IsReleased (void) { return (event () == EState::eReleased) ? true : false; }

    protected:
        struct Coordinates
        {
            uint16_t X;
            uint16_t Y;
        };

        const Configuration config;
        Coordinates         coordinates;

        virtual bool        isTouched      (void)          = 0;
        virtual Coordinates getCoordinates (void)          = 0;
        virtual uint16_t    getPos         (uint8_t v_cmd) = 0;

    private:
        enum class EState : uint8_t
        {
            ePressed,
            eReleased,
            eNeither
        };

        EState event (void);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
