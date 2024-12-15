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

Bitmap::Coordinates increaseCoordinates (Bitmap::Coordinates & vCoordinates, const uint8_t vHisteresis)
{
    vCoordinates.X = vCoordinates.X + vHisteresis + ONE;
    vCoordinates.Y = vCoordinates.Y + vHisteresis + ONE;
    return vCoordinates;
}

TEST_F (TouchFixture, CheckIfTouchIsReleased)
{
    LOGW (MODULE, "CheckIfTouchIsReleased");

    Bitmap::Coordinates pressedCoordinates;
    pressedCoordinates.X = ONE_HUNDRED;
    pressedCoordinates.Y = ONE_HUNDRED;

    ON_CALL (oTouchHw, isTouched ()).WillByDefault (Invoke (&oTouchHw, &TouchHw::IsTouched));

    Sequence seq;
    for (uint8_t pressedNum = ZERO; pressedNum < TouchFixture::Timeout.Pressed + ONE; pressedNum++)
    {
        EXPECT_CALL (oTouchHw, getCoordinates ()).InSequence (seq)
                                                 .WillOnce   (Return (pressedCoordinates));
    }

    for (uint8_t releasedNum = ZERO; releasedNum < TouchFixture::Timeout.Released; releasedNum++)
    {
        EXPECT_CALL (oTouchHw, getCoordinates ()).InSequence (seq)
                                                 .WillOnce   (Return (increaseCoordinates (pressedCoordinates, Histeresis)));
    }

    oTouchHw.Event = ButtonSpace::EEvent::Untouched;
    for (uint8_t eventNum = ZERO; eventNum < TouchFixture::Timeout.Pressed + ONE; eventNum++)
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

TEST_F (TouchFixture, CheckIfTouchIsPressed)
{
    LOGW (MODULE, "CheckIfTouchIsPressed");

    Bitmap::Coordinates pressedCoordinates;
    pressedCoordinates.X = TWENTY;
    pressedCoordinates.Y = TWENTY;

    EXPECT_CALL (oTouchHw, isTouched      ()).WillRepeatedly (Return (true));
    EXPECT_CALL (oTouchHw, getCoordinates ()).WillRepeatedly (Return (pressedCoordinates));

    oTouchHw.Event = ButtonSpace::EEvent::Untouched;
    for (uint8_t eventNum = ZERO; eventNum < TouchFixture::Timeout.Pressed + ONE; eventNum++)
    {
        EXPECT_EQ (ButtonSpace::EEvent::Untouched, oTouchHw.Event);
        oTouchHw.Process ();
    }

    ASSERT_EQ (ButtonSpace::EEvent::Pressed, oTouchHw.Event);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
