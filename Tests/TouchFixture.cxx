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
    for (uint8_t pressedNum = ZERO; pressedNum < TouchFixture::TimeMax.Pressed + ONE; pressedNum++)
    {
        EXPECT_CALL (oTouchHw, getCoordinates ()).InSequence (seq)
                                                 .WillOnce   (Return (pressedCoordinates));
    }

    for (uint8_t releasedNum = ZERO; releasedNum < TouchFixture::TimeMax.Released; releasedNum++)
    {
        EXPECT_CALL (oTouchHw, getCoordinates ()).InSequence (seq)
                                                 .WillOnce   (Return (increaseCoordinates (pressedCoordinates, Histeresis)));
    }

    ButtonSpace::EState state = ButtonSpace::EState::eUntouched;
    for (uint8_t eventNum = ZERO; eventNum < TouchFixture::TimeMax.Pressed + ONE; eventNum++)
    {
        EXPECT_EQ (ButtonSpace::EState::eUntouched, state);
        state = oTouchHw.Event ();
    }

    ASSERT_EQ (ButtonSpace::EState::ePressed, state);

    state = ButtonSpace::EState::eUntouched;
    for (uint8_t eventNum = ZERO; eventNum < TouchFixture::TimeMax.Released; eventNum++)
    {
        EXPECT_EQ (ButtonSpace::EState::eUntouched, state);
        state = oTouchHw.Event ();
    }

    ASSERT_EQ (ButtonSpace::EState::eReleased, state);
}

TEST_F (TouchFixture, CheckIfTouchIsPressed)
{
    LOGW (MODULE, "CheckIfTouchIsPressed");

    Bitmap::Coordinates pressedCoordinates;
    pressedCoordinates.X = TWENTY;
    pressedCoordinates.Y = TWENTY;

    EXPECT_CALL (oTouchHw, isTouched      ()).WillRepeatedly (Return (true));
    EXPECT_CALL (oTouchHw, getCoordinates ()).WillRepeatedly (Return (pressedCoordinates));

    ButtonSpace::EState state = ButtonSpace::EState::eUntouched;
    for (uint8_t eventNum = ZERO; eventNum < TouchFixture::TimeMax.Pressed; eventNum++)
    {
        EXPECT_EQ (ButtonSpace::EState::eUntouched, state);
        state = oTouchHw.Event ();
    }

    ASSERT_EQ (ButtonSpace::EState::ePressed, state);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////