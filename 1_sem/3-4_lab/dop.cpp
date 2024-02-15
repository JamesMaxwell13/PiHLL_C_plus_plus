#include <iostream>
#include <string>
#include <vector>

std::string railFenceEncode(const std::string& plaintext, int rails) {
    std::vector<std::string> fence(rails, "");
    int rail = 0;
    int direction = 1;

    for (char c : plaintext) {
        fence[rail] += c;

        if (rail == 0)
            direction = 1;
        else if (rail == rails - 1)
            direction = -1;

        rail += direction;
    }

    std::string ciphertext;
    for (std::string& i : fence)
        ciphertext += i;

    return ciphertext;
}

std::string railFenceDecode(const std::string& ciphertext, int rails) {
    std::vector<std::string> fence(rails, "");
    std::vector<int> railLengths(rails, 0);
    int rail = 0;
    int direction = 1;

    for (int i = 0; i < ciphertext.length(); i++) {
        railLengths[rail]++;

        if (rail == 0)
            direction = 1;
        else if (rail == rails - 1)
            direction = -1;

        rail += direction;
    }

    int currentIndex = 0;
    for (int i = 0; i < rails; i++) {
        fence[i] = ciphertext.substr(currentIndex, railLengths[i]);
        currentIndex += railLengths[i];
    }

    std::string plaintext;
    rail = 0;
    direction = 1;

    for (int i = 0; i < ciphertext.length(); i++) {
        plaintext += fence[rail][0];
        fence[rail] = fence[rail].substr(1);

        if (rail == 0)
            direction = 1;
        else if (rail == rails - 1)
            direction = -1;

        rail += direction;
    }

    return plaintext;
}

int main() {
    std::string plaintext;
    getline(std::cin, plaintext);

    int rails = 3;

    std::string encodedText = railFenceEncode(plaintext, rails);
    std::cout << "Encoded Text: " << encodedText << std::endl;

    std::string decodedText = railFenceDecode(encodedText, rails);
    std::cout << "Decoded Text: " << decodedText << std::endl;

    return 0;
}