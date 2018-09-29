#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <bint.hpp>
#include <crypto.hpp>
#include <utils.hpp>

using ::testing::Eq;

class CryptoTest : public ::testing::Test
{
public:
    CryptoTest()           = default;
    ~CryptoTest() override = default;

protected:
};

TEST_F( CryptoTest, testEnc )
{
    bint expected_ciphertext(
        "2e696bfa5f8b0f49e66fc8fe44174112ff9007b029ef1b6f" );

    bint key( "AAAAAAAAAAAAAAAA" );
    bint iv( 0 );

    const char* input_text = "AAAAAAAAAAAAAAAA";
    bint input( reinterpret_cast<const unsigned char*>( input_text ),
                strlen( input_text ) );

    bint output;
    bint full_circle;

    auto result = static_cast<int>(
        enc_encrypt_cipher( key, iv, input, output, EVP_des_cbc() ) );
    EXPECT_THAT( result, Eq( 1 ) );
    EXPECT_THAT( output, Eq( expected_ciphertext ) );

    result = static_cast<int>(
        enc_decrypt_cipher( key, iv, output, full_circle, EVP_des_cbc() ) );
    EXPECT_THAT( result, Eq( 1 ) );
    EXPECT_THAT( full_circle, Eq( input ) );
}
