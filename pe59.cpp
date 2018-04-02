/*
 * pe59.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe59.hpp"
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <gint.hpp>
#include <iostream>
#include <utils.hpp>

std::string& pe59::name() { return name_; }
void         pe59::run()
{
    /*
     *
     * Each character on a computer is assigned a unique code and the
     * preferred standard is ASCII (American Standard Code for Information
     * Interchange). For example, uppercase A = 65, asterisk (*) = 42, and
     * lowercase k = 107.
     *
     * A modern encryption method is to take a text file, convert the bytes
     * to ASCII, then XOR each byte with a given value, taken from a secret
     * key. The advantage with the XOR function is that using the same
     * encryption key on the cipher text, restores the plain text; for
     * example, 65 XOR 42 = 107, then 107 XOR 42 = 65.
     *
     * For unbreakable encryption, the key is the same length as the plain
     * text message, and the key is made up of random bytes. The user would
     * keep the encrypted message and the encryption key in different
     * locations, and without both "halves", it is impossible to decrypt the
     * message.
     *
     * Unfortunately, this method is impractical for most users, so the
     * modified method is to use a password as a key. If the password is
     * shorter than the message, which is likely, the key is repeated
     * cyclically throughout the message. The balance for this method is
     * using a sufficiently long password key for security, but short enough
     * to be memorable.
     *
     * Your task has been made easy, as the encryption key consists of three
     * lower case characters. Using pe59_cipher.txt, a file containing the
     * encrypted ASCII codes, and the knowledge that the plain text must
     * contain common English words, decrypt the message and find the sum of
     * the ASCII values in the original text.
     *
     */

    std::ifstream data_file;
    data_file.open( "../data/pe59_cipher.txt" );

    std::string cipher_text;
    data_file >> cipher_text;

    boost::char_separator<char>                   sep( "," );
    boost::tokenizer<boost::char_separator<char>> bytes( cipher_text, sep );

    char start[] = { 'g', 'o', 'd' };

    int    password_idx = 0;
    size_t result       = 0;

    BOOST_FOREACH ( const std::string& byte_string, bytes )
    {
        char c = stoi( byte_string );
        char p = c ^ start[password_idx];
        //    std::cout << "string: " << byte_string
        //              << "; cipher: " << c
        //              << "; plain: " << p << std::endl;
        result += p;
        password_idx = ( password_idx + 1 ) % 3;
    }
    std::cout << std::endl;

    std::cout << name() << ": " << result << std::endl;
}
