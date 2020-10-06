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
        enum class EState : uint8_t
        {
            ePressed,
            eReleased,
            eUntouched
        };

        struct Coordinates
        {
            uint16_t X;
            uint16_t Y;
        };

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
        const Configuration config;
        Coordinates         coordinates = { ZERO, ZERO };

        virtual bool        isTouched      (void)          = 0;
        virtual Coordinates getCoordinates (void)          = 0;
        virtual uint16_t    getPos         (uint8_t v_cmd) = 0;
        EState              event          (void);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
