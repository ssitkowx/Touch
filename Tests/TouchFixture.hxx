#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "Touch.h"
#include "TouchHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class TouchFixture : public ::testing::Test
{
    public:
        static constexpr char *           MODULE       = (char *)"TouchFixture";
        const uint8_t                     Histeresis   = TWO;
        const struct ButtonSpace::Timeout Timeout      = { EIGHT,  
                                                           FOUR,
                                                           FOUR
                                                         };
        const TouchHw::Coefficients       Coefficients = { ONE_HUNDRED_TWENTY_EIGHT,
                                                           TWO,
                                                           2.68
                                                         };
        class SpiHw                       SpiHw;
        class TouchHw                     oTouchHw;

        TouchFixture  () : oTouchHw (Coefficients, Timeout, Histeresis, SpiHw) { }
        
        void TestBody () override { }
        void SetUp    () override { }
        void TearDown () override { }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////