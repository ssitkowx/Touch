///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "LoggerHw.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TouchFixture.hxx"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

using ::testing::Return;
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

TEST_F (TouchFixture, CheckIfDipslayIsReleased)
{
    LOGW (MODULE, "CheckIfDipslayIsReleased");

    Bitmap::Coordinates pressedCoordinates;
    pressedCoordinates.X = ONE_HUNDRED;
    pressedCoordinates.Y = ONE_HUNDRED;

    EXPECT_CALL (TouchHw, isTouched ())         .Times          (Config.Time.PressedMax + ONE + Config.Time.ReleasedMax)
                                                .WillRepeatedly (Return (true));

    Sequence seq;
    for (uint8_t pressedNum = ZERO; pressedNum < Config.Time.PressedMax + ONE; pressedNum++)
    {
        EXPECT_CALL (TouchHw, getCoordinates ()).InSequence (seq)
                                                .WillOnce   (Return (pressedCoordinates));
    }

    for (uint8_t releasedNum = ZERO; releasedNum < Config.Time.ReleasedMax; releasedNum++)
    {
        EXPECT_CALL (TouchHw, getCoordinates ()).InSequence (seq)
                                                .WillOnce   (Return (increaseCoordinates (pressedCoordinates, Config.Histeresis)));
    }

    Touch<decltype(TouchHw)>::EState state = Touch<decltype(TouchHw)>::EState::eUntouched;
    for (uint8_t eventNum = ZERO; eventNum < Config.Time.PressedMax + ONE; eventNum++)
    {
        ASSERT_EQ (Touch<decltype(TouchHw)>::EState::eUntouched, state);
        state = TouchHw.Event ();
    }

    ASSERT_EQ (Touch<decltype(TouchHw)>::EState::ePressed, state);

    state = Touch<decltype(TouchHw)>::EState::eUntouched;
    for (uint8_t eventNum = ZERO; eventNum < Config.Time.ReleasedMax; eventNum++)
    {
        ASSERT_EQ (Touch<decltype(TouchHw)>::EState::eUntouched, state);
        state = TouchHw.Event ();
    }

    ASSERT_EQ (Touch<decltype(TouchHw)>::EState::eReleased, state);
}

TEST_F (TouchFixture, CheckIfDipslayIsUntouchedAfterTooShortTimePressed)
{
    LOGW (MODULE, "CheckIfDipslayIsUntouchedAfterTooShortTimePressed");

    Bitmap::Coordinates pressedCoordinates;
    pressedCoordinates.X = TWENTY;
    pressedCoordinates.Y = TWENTY;

    EXPECT_CALL (TouchHw, isTouched      ()).WillRepeatedly (Return (true));
    EXPECT_CALL (TouchHw, getCoordinates ()).WillRepeatedly (Return (pressedCoordinates));

    Touch<decltype(TouchHw)>::EState state = Touch<decltype(TouchHw)>::EState::eUntouched;
    for (uint8_t eventNum = ZERO; eventNum < Config.Time.PressedMax - ONE; eventNum++)
    {
        state = TouchHw.Event ();
        ASSERT_EQ (Touch<decltype(TouchHw)>::EState::eUntouched, state);
    }
}

TEST_F (TouchFixture, CheckIfDipslayIsPressed)
{
    LOGW (MODULE, "CheckIfDipslayIsTouched");

    Bitmap::Coordinates pressedCoordinates;
    pressedCoordinates.X = TWENTY;
    pressedCoordinates.Y = TWENTY;

    EXPECT_CALL (TouchHw, isTouched      ()).WillRepeatedly (Return (true));
    EXPECT_CALL (TouchHw, getCoordinates ()).WillRepeatedly (Return (pressedCoordinates));

    Touch<decltype(TouchHw)>::EState state = Touch<decltype(TouchHw)>::EState::eUntouched;
    for (uint8_t eventNum = ZERO; eventNum < Config.Time.PressedMax + ONE; eventNum++)
    {
        ASSERT_EQ (Touch<decltype(TouchHw)>::EState::eUntouched, state);
        state = TouchHw.Event ();
    }

    ASSERT_EQ (Touch<decltype(TouchHw)>::EState::ePressed, state);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////