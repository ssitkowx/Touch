#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Touch.h"
#include "SpiHw.h"
#include "gmock/gmock.h"

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

        explicit TouchHw (const Coefficients v_coefficient, 
                          const Touch<TouchHw>::Config v_touchConfig,
                          SpiHw & v_spiHw) : Touch<TouchHw> (v_touchConfig),
                                             coefficient    (v_coefficient),
                                             spiHw          (v_spiHw)
        { }
       ~TouchHw () = default;

        Touch::Event;
        Touch::coordinates;

        MOCK_METHOD0 (Process       , void                (void));
        MOCK_METHOD0 (isTouched     , bool                (void));
        MOCK_METHOD0 (getCoordinates, Bitmap::Coordinates (void));
        MOCK_METHOD1 (getPos        , uint16_t            (uint8_t));

    private:
        const Coefficients coefficient;
        SpiHw &            spiHw;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////