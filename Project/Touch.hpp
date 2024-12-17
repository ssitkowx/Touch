#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.hpp"
#include "Bitmap.hpp"
#include "Button.hpp"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <class DERIVED_TYPE>
class Touch : public Button <DERIVED_TYPE>
{
    friend DERIVED_TYPE;
    DERIVED_TYPE & derivedType = static_cast <DERIVED_TYPE &>(*this);

    public:
        Bitmap::Coordinates Coordinates;

        explicit Touch (const ButtonSpace::Timeout vTimeout, const uint8_t vHisteresis) : Button <DERIVED_TYPE>(vTimeout),
                                                                                          histeresis (vHisteresis) { }
        bool IsTouched (void)
        {
            bool state  = false;
            Coordinates = getCoordinates ();
            
            if ((Coordinates.X >= histeresis) && (Coordinates.Y >= histeresis)) { state = true;  }
            else                                                                { state = false; }

            return state;
        }

    private:
        const uint8_t histeresis;

        ~Touch () = default;

        uint16_t            getPos         (const uint8_t vCmd) { return derivedType.getPos (vCmd); }
        Bitmap::Coordinates getCoordinates (void)               { return derivedType.getCoordinates (); }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////