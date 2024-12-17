#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.hpp"
#include "Touch.hpp"
#include "TouchHw.hpp"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class TouchFixture : public ::testing::Test
{
    public:
        static constexpr char *           MODULE       = (char *)"TouchFixture";
        const uint8_t                     Histeresis   = FIVE;
        const struct ButtonSpace::Timeout Timeout      = { EIGHT,  
                                                           FOUR,
                                                           FOUR
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
