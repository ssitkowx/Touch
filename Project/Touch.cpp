///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "Touch.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Touch::EState Touch::event (void)
{
    static EState state = EState::eNeither;
    if (isTouched () == true)
    {
        static bool    isPressed = false;
        static uint8_t timePressed;
        static uint8_t timeReleased;

        Touch::Coordinates newCoordinates = getCoordinates ();
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
                else { state = EState::eNeither; }
            }
            else { state = EState::eNeither; }

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
                else { state = EState::eNeither; }
            }
            else { state = EState::eNeither; }

            timePressed = ZERO;
        }

        coordinates = newCoordinates;
        return state;
    }

    return EState::eNeither;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
