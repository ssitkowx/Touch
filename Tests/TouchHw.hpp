#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Touch.hpp"
#include "SpiHw.hpp"
#include <gmock/gmock.h>

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class TouchHw final : public Touch<TouchHw>
{
    public:
        struct Coefficients
        {
            uint8_t Constant;
            double  Width;
            double  Length;
        };

        explicit TouchHw (const Coefficients         vCoefficient, 
                          const ButtonSpace::Timeout Timeout,
                          const uint8_t              vHysteresis,
                          SpiHw & vSpiHw) : Touch<TouchHw> (Timeout, vHysteresis),
                                             coefficient   (vCoefficient),
                                             spiHw         (vSpiHw)
        { }
       ~TouchHw () = default;

        using Touch::coordinates;

        MOCK_METHOD0 (isTouched     , bool                (void));
        MOCK_METHOD0 (getCoordinates, Bitmap::Coordinates (void));
        MOCK_METHOD1 (getPos        , uint16_t            (uint8_t));

        bool IsTouched (void) { return Touch<TouchHw>::isTouched (); }

    private:
        const Coefficients coefficient;
        SpiHw &            spiHw;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
