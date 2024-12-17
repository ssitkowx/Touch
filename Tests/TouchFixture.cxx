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
    LOGW (MODULE, "CheckIfTouchIsReleased");

    Bitmap::Coordinates pressedCoordinates;
    pressedCoordinates.X = ONE_HUNDRED;
    pressedCoordinates.Y = ONE_HUNDRED;

    Sequence seq;
    for (uint8_t pressedNum = ZERO; pressedNum < TouchFixture::Timeout.Pressed; pressedNum++)
    {
        EXPECT_CALL (oTouchHw, getCoordinates ()).InSequence (seq)
                                                 .WillOnce   (Return (pressedCoordinates));
    }

    pressedCoordinates.X = ZERO;
    pressedCoordinates.Y = ZERO;
    for (uint8_t releasedNum = ZERO; releasedNum < TouchFixture::Timeout.Released; releasedNum++)
    {
        EXPECT_CALL (oTouchHw, getCoordinates ()).InSequence (seq)
                                                 .WillOnce   (Return (pressedCoordinates));
    }

    oTouchHw.Event = ButtonSpace::EEvent::Untouched;
    for (uint8_t eventNum = ZERO; eventNum < TouchFixture::Timeout.Pressed; eventNum++)
    {
        EXPECT_EQ (ButtonSpace::EEvent::Untouched, oTouchHw.Event);
        oTouchHw.Process ();
    }

    ASSERT_EQ (ButtonSpace::EEvent::Pressed, oTouchHw.Event);

    oTouchHw.Event = ButtonSpace::EEvent::Untouched;
    for (uint8_t eventNum = ZERO; eventNum < TouchFixture::Timeout.Released; eventNum++)
    {
        EXPECT_EQ (ButtonSpace::EEvent::Untouched, oTouchHw.Event);
        oTouchHw.Process ();
    }

    ASSERT_EQ (ButtonSpace::EEvent::Released, oTouchHw.Event);
}

TEST_F (TouchFixture, CheckIfTouchIsHoldAndReleased)
{
    LOGW (MODULE, "CheckIfTouchIsHoldAndReleased");

    Bitmap::Coordinates holdCoordinates;
    holdCoordinates.X = ONE_HUNDRED;
    holdCoordinates.Y = ONE_HUNDRED;

    Sequence seq;
    for (uint8_t holdNum = ZERO; holdNum < TouchFixture::Timeout.Hold; holdNum++)
    {
        EXPECT_CALL (oTouchHw, getCoordinates ()).InSequence (seq)
                                                 .WillOnce   (Return (holdCoordinates));
    }

    holdCoordinates.X = ZERO;
    holdCoordinates.Y = ZERO;
    for (uint8_t releasedNum = ZERO; releasedNum < TouchFixture::Timeout.Released; releasedNum++)
    {
        EXPECT_CALL (oTouchHw, getCoordinates ()).InSequence (seq)
                                                 .WillOnce   (Return (holdCoordinates));
    }

    oTouchHw.Event = ButtonSpace::EEvent::Untouched;
    for (uint8_t eventNum = ZERO; eventNum < TouchFixture::Timeout.Hold; eventNum++)
    {
        if (eventNum == TouchFixture::Timeout.Pressed) { EXPECT_EQ (ButtonSpace::EEvent::Pressed  , oTouchHw.Event); }
        else                                           { EXPECT_EQ (ButtonSpace::EEvent::Untouched, oTouchHw.Event); }

        oTouchHw.Process ();
    }

    ASSERT_EQ (ButtonSpace::EEvent::Hold, oTouchHw.Event);

    oTouchHw.Event = ButtonSpace::EEvent::Untouched;
    for (uint8_t eventNum = ZERO; eventNum < TouchFixture::Timeout.Released; eventNum++)
    {
        EXPECT_EQ (ButtonSpace::EEvent::Untouched, oTouchHw.Event);
        oTouchHw.Process ();
    }

    ASSERT_EQ (ButtonSpace::EEvent::Released, oTouchHw.Event);
}
///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
