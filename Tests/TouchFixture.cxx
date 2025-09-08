///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "TouchHw.hpp"
#include "LoggerHw.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TouchFixture.hxx"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

using ::testing::Return;
using ::testing::Invoke;
using ::testing::Sequence;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEST_F (TouchFixture, CheckIfTouchIsPressedAndReleased)
{
    LOGW (Module, "CheckIfTouchIsReleased");

    Bitmap::Coordinates pressedCoordinates;
    pressedCoordinates.X = 100;
    pressedCoordinates.Y = 100;

    Sequence seq;
    for (uint8_t pressedNum = 0; pressedNum < TouchFixture::Timeout.Pressed; pressedNum++)
    {
        EXPECT_CALL (oTouchHw, getCoordinates ()).InSequence (seq)
                                                 .WillOnce   (Return (pressedCoordinates));
    }

    pressedCoordinates.X = 0;
    pressedCoordinates.Y = 0;
    for (uint8_t releasedNum = 0; releasedNum < TouchFixture::Timeout.Released; releasedNum++)
    {
        EXPECT_CALL (oTouchHw, getCoordinates ()).InSequence (seq)
                                                 .WillOnce   (Return (pressedCoordinates));
    }

    oTouchHw.Event = ButtonSpace::EEvent::Untouched;
    for (uint8_t eventNum = 0; eventNum < TouchFixture::Timeout.Pressed; eventNum++)
    {
        EXPECT_EQ (ButtonSpace::EEvent::Untouched, oTouchHw.Event);
        oTouchHw.Process ();
    }

    ASSERT_EQ (ButtonSpace::EEvent::Pressed, oTouchHw.Event);

    oTouchHw.Event = ButtonSpace::EEvent::Untouched;
    for (uint8_t eventNum = 0; eventNum < TouchFixture::Timeout.Released; eventNum++)
    {
        EXPECT_EQ (ButtonSpace::EEvent::Untouched, oTouchHw.Event);
        oTouchHw.Process ();
    }

    ASSERT_EQ (ButtonSpace::EEvent::Released, oTouchHw.Event);
}

TEST_F (TouchFixture, CheckIfTouchIsHoldAndReleased)
{
    LOGW (Module, "CheckIfTouchIsHoldAndReleased");

    Bitmap::Coordinates holdCoordinates;
    holdCoordinates.X = 100;
    holdCoordinates.Y = 100;

    Sequence seq;
    for (uint8_t holdNum = 0; holdNum < TouchFixture::Timeout.Hold; holdNum++)
    {
        EXPECT_CALL (oTouchHw, getCoordinates ()).InSequence (seq)
                                                 .WillOnce   (Return (holdCoordinates));
    }

    holdCoordinates.X = 0;
    holdCoordinates.Y = 0;
    for (uint8_t releasedNum = 0; releasedNum < TouchFixture::Timeout.Released; releasedNum++)
    {
        EXPECT_CALL (oTouchHw, getCoordinates ()).InSequence (seq)
                                                 .WillOnce   (Return (holdCoordinates));
    }

    oTouchHw.Event = ButtonSpace::EEvent::Untouched;
    for (uint8_t eventNum = 0; eventNum < TouchFixture::Timeout.Hold; eventNum++)
    {
        if (eventNum == TouchFixture::Timeout.Pressed) { EXPECT_EQ (ButtonSpace::EEvent::Pressed  , oTouchHw.Event); }
        else                                           { EXPECT_EQ (ButtonSpace::EEvent::Untouched, oTouchHw.Event); }

        oTouchHw.Process ();
    }

    ASSERT_EQ (ButtonSpace::EEvent::Hold, oTouchHw.Event);

    oTouchHw.Event = ButtonSpace::EEvent::Untouched;
    for (uint8_t eventNum = 0; eventNum < TouchFixture::Timeout.Released; eventNum++)
    {
        EXPECT_EQ (ButtonSpace::EEvent::Untouched, oTouchHw.Event);
        oTouchHw.Process ();
    }

    ASSERT_EQ (ButtonSpace::EEvent::Released, oTouchHw.Event);
}
///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
