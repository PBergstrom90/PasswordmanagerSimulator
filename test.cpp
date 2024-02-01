#include <string>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include "user.h"
#include "crack.h"
#include <gtest/gtest.h>

class UserTests : public ::testing::Test {
protected:
void SetUp() override { 

    }
};

TEST_F(UserTests, PasswordDoesNotHaveUpperCaseAndShouldFail) {

    // ARRANGE
    std::string password = "hejsan!1";
    // ACT
    bool b = isStrongPassword(password);
    // ASSERT
    ASSERT_EQ(b,false);
}

TEST_F(UserTests, PasswordDoesNotHaveLowerCaseAndShouldFail) {

    std::string password = "HEJSAN!1";
    bool b = isStrongPassword(password);
    ASSERT_EQ(b,false);
}

TEST_F(UserTests, PasswordDoesNotHaveSpecialCharAndShouldFail) {

    std::string password = "Hejsan1";
    bool b = isStrongPassword(password);
    ASSERT_EQ(b,false);
}

TEST_F(UserTests, PasswordDoesNotHaveDigitAndShouldFail) {

    std::string password = "Hejsan!";
    bool b = isStrongPassword(password);
    ASSERT_EQ(b,false);
}

TEST_F(UserTests, PasswordIsTooShortAndShouldFail) {

    std::string password = "Hej1!";
    bool b = isStrongPassword(password);
    ASSERT_EQ(b,false);
}

TEST_F(UserTests, PasswordIsCorrectAndShouldSucceed) {

    std::string password = "Hejsan1!";
    bool b = isStrongPassword(password);
    ASSERT_EQ(b,true);
}