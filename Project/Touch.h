#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "Bitmap.h"
#include "Button.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <class DERIVED_TYPE>
class Touch : public Button <DERIVED_TYPE>
{
    friend DERIVED_TYPE;
    DERIVED_TYPE & derivedType = static_cast <DERIVED_TYPE &>(*this);

    public:
        explicit Touch (const ButtonSpace::TimeMax vTimeMax, const uint8_t vHisteresis) : Button <DERIVED_TYPE>(vTimeMax), histeresis (vHisteresis) { }

    private:
        const uint8_t histeresis;
        Bitmap::Coordinates coordinates = { ZERO, ZERO };

        ~Touch () = default;
        bool isTouched (void)
        {
            bool                state          = false;
            Bitmap::Coordinates newCoordinates = getCoordinates ();
            
            if (((coordinates.X - histeresis) <= newCoordinates.X) && (newCoordinates.X <= (coordinates.X + histeresis)) &&
                ((coordinates.Y - histeresis) <= newCoordinates.Y) && (newCoordinates.Y <= (coordinates.Y + histeresis))) { state = true;  }
            else                                                                                                          { state = false; }

            coordinates = newCoordinates;
            return state;
        }
        
        uint16_t            getPos         (uint8_t v_cmd) { return derivedType.getPos (v_cmd); }
        Bitmap::Coordinates getCoordinates (void)          { return derivedType.getCoordinates (); }      
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
