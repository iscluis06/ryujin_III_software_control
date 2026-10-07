#include "commands/show_slots_command.h"


#include <fstream>
#include <gtest/gtest.h>

#include "stores/memory_slots_store_mock.h"

class ShowSlotsCommandTest : public testing::Test {
protected:
    static void SetUpTestSuite() {
        mock = std::make_shared<testing::NiceMock<MemorySlotsStoreMock>>(".");
        default_array = std::vector<unsigned char>(65, 0);
    }
    static void TearDownTestSuite() { mock.reset(); }
    static std::shared_ptr<testing::NiceMock<MemorySlotsStoreMock>> mock;
    static std::vector<unsigned char> default_array;
};

std::shared_ptr<testing::NiceMock<MemorySlotsStoreMock>> ShowSlotsCommandTest::mock;
std::vector<unsigned char> ShowSlotsCommandTest::default_array;

TEST_F(ShowSlotsCommandTest, ExecuteSuccess) {
    EXPECT_CALL(*(mock.get()), PrintAll).Times(1);
    ShowSlotsCommand show_slots_command(mock);
    std::ofstream gif_file{"./gif_array"};
    gif_file << "";
    gif_file.close();
    std::ofstream jpeg_file{"./jpeg_array"};
    jpeg_file << "";
    jpeg_file.close();
    EXPECT_EQ(show_slots_command.Execute(), true);
}
