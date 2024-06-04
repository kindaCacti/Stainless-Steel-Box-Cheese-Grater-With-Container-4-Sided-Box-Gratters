#include <gtest/gtest.h>
#include "bot.h"
#include "../CheesyApi/board.h"

TEST(TEST_BOT, CONVERT_TO_CHESS_NOTATION){
    Bot bot;
    std::string cn = bot.convertToChessNotation(1,1);
    ASSERT_EQ(cn, std::string("b7"));
}