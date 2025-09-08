#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Touch.hpp"
#include "TouchHw.hpp"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class TouchFixture : public ::testing::Test
{
    public:
        static constexpr char *           Module       = (char *)"TouchFixture";
        const uint8_t                     Histeresis   = 5;
        const struct ButtonSpace::Timeout Timeout      = { 8,
                                                           4,
                                                           4
                                                         };
        const TouchHw::Coefficients       Coefficients = { 1,
                                                           1
                                                         };
        class TouchHw                     oTouchHw;
        class SpiTouchHw                  SpiTouchHw;

        TouchFixture  () : oTouchHw (Timeout, Histeresis, Coefficients, SpiTouchHw) { }
        
        void TestBody () override { }
        void SetUp    () override { }
        void TearDown () override { }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
