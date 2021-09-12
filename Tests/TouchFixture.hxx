#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "TouchHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class TouchFixture : public ::testing::Test
{
    public:
        static constexpr char *      MODULE       = (char *)"TouchFixture";
        const TouchHw::Config        Config       = { TWO,  
                                                      FOUR,  
                                                      EIGHT
                                                    };
        const TouchHw::Coefficients  Coefficients = { ONE_HUNDRED_TWENTY_EIGHT,
                                                      TWO,
                                                      2.68
                                                    };
        class SpiHw                  SpiHw;
        class TouchHw                oTouchHw;

        TouchFixture  () : oTouchHw (Coefficients, Config, SpiHw) { }
        void TestBody () override { }
        void SetUp    () override { }
        void TearDown () override { }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////