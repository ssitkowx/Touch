///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "LoggerMock.h"
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

Rectangle::Coordinates increaseCoordinates (Rectangle::Coordinates & v_coordinates, uint8_t v_histeresis)
{
    v_coordinates.X = v_coordinates.X + v_histeresis + ONE;
    v_coordinates.Y = v_coordinates.Y + v_histeresis + ONE;
    return v_coordinates;
}

TEST_F (TouchFixture, CheckIfDipslayIsReleased)
{
    LOGW (MODULE, "CheckIfDipslayIsReleased");

    Rectangle::Coordinates pressedCoordinates;
    pressedCoordinates.X = ONE_HUNDRED;
    pressedCoordinates.Y = ONE_HUNDRED;

    EXPECT_CALL (TouchMock, isTouched ())         .Times          (Config.Time.PressedMax + ONE + Config.Time.ReleasedMax)
                                                  .WillRepeatedly (Return (true));

    Sequence seq;
    for (uint8_t pressedNum = ZERO; pressedNum < Config.Time.PressedMax + ONE; pressedNum++)
    {
        EXPECT_CALL (TouchMock, getCoordinates ()).InSequence (seq)
                                                  .WillOnce   (Return (pressedCoordinates));
    }

    for (uint8_t releasedNum = ZERO; releasedNum < Config.Time.ReleasedMax; releasedNum++)
    {
        EXPECT_CALL (TouchMock, getCoordinates ()).InSequence (seq)
                                                  .WillOnce   (Return (increaseCoordinates (pressedCoordinates, Config.Histeresis)));
    }

    Touch::EState state = Touch::EState::eUntouched;
    for (uint8_t eventNum = ZERO; eventNum < Config.Time.PressedMax + ONE; eventNum++)
    {
        ASSERT_EQ (Touch::EState::eUntouched, state);
        state = TouchMock.event ();
    }

    ASSERT_EQ (Touch::EState::ePressed, state);

    state = Touch::EState::eUntouched;
    for (uint8_t eventNum = ZERO; eventNum < Config.Time.ReleasedMax; eventNum++)
    {
        ASSERT_EQ (Touch::EState::eUntouched, state);
        state = TouchMock.event ();
    }

    ASSERT_EQ (Touch::EState::eReleased, state);
}

TEST_F (TouchFixture, CheckIfDipslayIsUntouchedAfterTooShortTimePressed)
{
    LOGW (MODULE, "CheckIfDipslayIsUntouchedAfterTooShortTimePressed");

    Rectangle::Coordinates pressedCoordinates;
    pressedCoordinates.X = TWENTY;
    pressedCoordinates.Y = TWENTY;

    EXPECT_CALL (TouchMock, isTouched      ()).WillRepeatedly (Return (true));
    EXPECT_CALL (TouchMock, getCoordinates ()).WillRepeatedly (Return (pressedCoordinates));

    Touch::EState state = Touch::EState::eUntouched;
    for (uint8_t eventNum = ZERO; eventNum < Config.Time.PressedMax - ONE; eventNum++)
    {
        state = TouchMock.event ();
        ASSERT_EQ (Touch::EState::eUntouched, state);
    }
}

TEST_F (TouchFixture, CheckIfDipslayIsPressed)
{
    LOGW (MODULE, "CheckIfDipslayIsTouched");

    Rectangle::Coordinates pressedCoordinates;
    pressedCoordinates.X = TWENTY;
    pressedCoordinates.Y = TWENTY;

    EXPECT_CALL (TouchMock, isTouched      ()).WillRepeatedly (Return (true));
    EXPECT_CALL (TouchMock, getCoordinates ()).WillRepeatedly (Return (pressedCoordinates));

    Touch::EState state = Touch::EState::eUntouched;
    for (uint8_t eventNum = ZERO; eventNum < Config.Time.PressedMax + ONE; eventNum++)
    {
        ASSERT_EQ (Touch::EState::eUntouched, state);
        state = TouchMock.event ();
    }

    ASSERT_EQ (Touch::EState::ePressed, state);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////