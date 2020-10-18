///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Touch.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Touch::EState Touch::event (void)
{
    static EState state = EState::eUntouched;
    if (isTouched () == true)
    {
        static bool    isPressed = false;
        static uint8_t timePressed;
        static uint8_t timeReleased;

        Rectangle::Coordinates newCoordinates = getCoordinates ();
        if (((coordinates.X - config.Histeresis) <= newCoordinates.X) && (newCoordinates.X <= (coordinates.X + config.Histeresis)) &&
            ((coordinates.Y - config.Histeresis) <= newCoordinates.Y) && (newCoordinates.Y <= (coordinates.Y + config.Histeresis)))
        {
            if (isPressed == false)
            {
                if (++timePressed == config.Time.PressedMax)
                {
                    isPressed   = true;
                    timePressed = ZERO;
                    state       = EState::ePressed;
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

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
