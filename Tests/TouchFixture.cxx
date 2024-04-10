///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "TouchHw.h"
#include "LoggerHw.h"
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

Bitmap::Coordinates increaseCoordinates (Bitmap::Coordinates & v_coordinates, uint8_t v_histeresis)
{
    v_coordinates.X = v_coordinates.X + v_histeresis + ONE;
    v_coordinates.Y = v_coordinates.Y + v_histeresis + ONE;
    return v_coordinates;
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