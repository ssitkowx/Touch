#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "TouchMock.hxx"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class TouchFixture : public ::testing::Test
{
    public:
        static constexpr char *        MODULE = (char *)"TouchFixture";
        const TouchMock::Configuration Config = { TWO,  FOUR,  EIGHT };
        TouchMock                      TouchMock;

        TouchFixture  () : TouchMock (Config) { }
        void TestBody () override { }
        void SetUp    () override { }
        void TearDown () override { }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////