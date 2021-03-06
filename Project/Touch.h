#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "Bitmap.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <class DERIVED_TYPE>
class Touch
{
    friend DERIVED_TYPE;
    DERIVED_TYPE & derivedType = static_cast <DERIVED_TYPE &>(*this);

    public:
        enum class EState : uint8_t
        {
            ePressed,
            eReleased,
            eUntouched
        };

        struct Config
        {
            uint8_t Histeresis;
            struct
            {
                uint8_t PressedMax;
                uint8_t ReleasedMax;
            } Time;
        };

        explicit Touch (Config v_config) : config (v_config) { }

        EState Event (void)
        {
            static EState state = EState::eUntouched;
            if (isTouched () == true)
            {
                static bool    isPressed = false;
                static uint8_t timePressed;
                static uint8_t timeReleased;

                Bitmap::Coordinates newCoordinates = GetCoordinates ();
                if (((coordinates.X - config.Histeresis) <= newCoordinates.X) && (newCoordinates.X <= (coordinates.X + config.Histeresis)) &&
                    ((coordinates.Y - config.Histeresis) <= newCoordinates.Y) && (newCoordinates.Y <= (coordinates.Y + config.Histeresis)))
                {
                    if (isPressed == false)
                    {
                        if (++timePressed == config.Time.PressedMax)
                        {
                            isPressed = true;
                            timePressed = ZERO;
                            state = EState::ePressed;
                        }
                        else { state = EState::eUntouched; }
                    }
                    else { state = EState::eUntouched; }

                    timeReleased = ZERO;
                }
                else
                {
                    if (isPressed == true)
                    {
                        if (++timeReleased == config.Time.ReleasedMax)
                        {
                            isPressed    = false;
                            timeReleased = ZERO;
                            state        = EState::eReleased;
                        }
                        else { state = EState::eUntouched; }
                    }
                    else { state = EState::eUntouched; }

                    timePressed = ZERO;
                }

                coordinates = newCoordinates;
                return state;
            }

            return EState::eUntouched;
        }

        bool                IsPressed      (void)          { return (Event () == EState::ePressed ) ? true : false; }
        bool                IsReleased     (void)          { return (Event () == EState::eReleased) ? true : false; }
        Bitmap::Coordinates GetCoordinates (void)          { return derivedType.getCoordinates ();                  }

    protected:
        const Config        config;
        Bitmap::Coordinates coordinates = { ZERO, ZERO };

        bool                isTouched      (void)          { return derivedType.isTouched ();      }
        uint16_t            getPos         (uint8_t v_cmd) { return derivedType.getPos    (v_cmd); }

    private:
        ~Touch () = default;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
