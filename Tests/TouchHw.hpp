#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Touch.hpp"
#include <gmock/gmock.h>
#include "SpiTouchHw.hpp"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class TouchHw final : public Touch<TouchHw>
{
    public:
        struct Coefficients
        {
            double Width;
            double Length;
        };

        explicit TouchHw (const ButtonSpace::Timeout Timeout,
                          const uint8_t              vHysteresis,
                          const Coefficients         vCoefficient, 
                          SpiTouchHw & vSpiTouchHw) : Touch<TouchHw> (Timeout, vHysteresis),
                                                      coefficient    (vCoefficient),
                                                      spiTouchHw     (vSpiTouchHw)
        { }
       ~TouchHw () = default;

        using Touch::Coordinates;

        MOCK_METHOD0 (getCoordinates, Bitmap::Coordinates (void));
        MOCK_METHOD1 (getPos        , uint16_t            (uint8_t));

    private:
        const Coefficients coefficient;
        SpiTouchHw &       spiTouchHw;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
