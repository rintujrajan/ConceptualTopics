#include <iostream>
#include <cmath>
using namespace std;

const int TOTAL_CHARS = 255;
const int PRIME = 101;
int searchFirstOccurenceOfPattern(string originalStr, string patternStr)
{

    int ret = -1;
    int strLen = originalStr.size();
    int patternLen = patternStr.length();
    if (originalStr == patternStr)
    {
        ret = 0;
    }
    else if (patternLen < strLen)
    {
        int patternHash = 0;
        int strHash = 0;
        int temp = 0;
        int hashOfPatternLength = 1;

        /* although ((256%101)*256)%101 is the same as 2562 % 101,
            to avoid overflowing integer maximums when the pattern string is longer, the pattern length base offset is pre-calculated in a loop,
            modulating the result each iteration
        */
        for (int i = 0; i < patternLen - 1; i++)
            hashOfPatternLength = (hashOfPatternLength * TOTAL_CHARS) % PRIME;
        std::cout << "hashOfPatternLength : " << hashOfPatternLength << "\n";

        for (int i = 0; i < patternLen; ++i)
        {
            unsigned int curChar = patternStr[i];
            unsigned int multiplier = pow(TOTAL_CHARS, patternLen - i - 1);
            temp = patternStr[i] * pow(TOTAL_CHARS, patternLen - i - 1);
            patternHash = (patternHash + temp) % PRIME; //calculate hash of the pattern
            curChar = originalStr[i];
            temp = originalStr[i] * pow(TOTAL_CHARS, patternLen - i - 1);
            strHash = (strHash + temp) % PRIME; //calculate hash value of the first sliding window from input string
            std::cout << patternHash << " " << strHash << "\n";
        }
        patternHash = strHash = 0;
        for (int i = 0; i < patternLen; ++i)
        {
            patternHash = ((patternHash * TOTAL_CHARS) + patternStr[i]) % PRIME; //calculate hash of the pattern
            strHash = ((strHash * TOTAL_CHARS) + originalStr[i]) % PRIME;        //calculate hash value of the first sliding window from input string
            std::cout << patternHash << " " << strHash << "\n";
        }
        cout << "\npatternHash : " << patternHash << endl;
        cout << "first window strHash : " << strHash << endl;

        for (int i = 0; i < strLen - patternLen + 1; ++i)
        {
            if (patternHash == strHash)
            {
                // we found a hash mash, check for each characters to see if chars match
                // cout << "hash match found at pos " << i << endl;
                bool patternMatched = true;
                int localI = i;
                for (int looper = 0; looper < patternLen; ++looper)
                {
                    if (originalStr[localI] != patternStr[looper])
                    {
                        patternMatched = false;
                        break;
                    }
                    localI++;
                }
                // cout << std::boolalpha << "patternMatched : " << patternMatched << "\n";
                if (patternMatched)
                {
                    // cout << "match found at pos " << i << endl;
                    ret = i;
                    break;
                }
            }

            // we did not find a match, we move the sliding window by one char forward
            if (i < strLen - patternLen)
            {
                int charBegin = originalStr[i];
                int charEnd1 = originalStr[i + patternLen];
                int prevHash = (PRIME + strHash);
                int hashofFirstChar = (originalStr[i] * hashOfPatternLength);
                int firstCalc = prevHash - hashofFirstChar;
                int secondCalc = firstCalc * TOTAL_CHARS;
                int thirdCalc = secondCalc + originalStr[i + patternLen];
                int fourthCalc = thirdCalc % PRIME;
                // strHash = (afterRemovingFirstChar + newChar) % PRIME;
                strHash = ((strHash - (originalStr[i] * hashOfPatternLength)) * TOTAL_CHARS + originalStr[i + patternLen]) % PRIME;

                // strHash = (TOTAL_CHARS * (strHash - originalStr[i] * h) + originalStr[i + patternLen]) % PRIME;
                if (strHash < 0)
                    strHash += PRIME;
                // cout << "new strHash : " << strHash << endl;
            }
        }
    }

    return ret;
}
int searchPattern(string txt, string pat)
{
    int patternLen = pat.length();
    int txtLen = txt.length();
    int i, j;
    int patternHash = 0; // hash value for pattern
    int txtHash = 0;     // hash value for txt
    int hashOfPatternLength = 1;

    // The value of hashOfPatternLength would be "pow(TOTAL_CHARS, patternLen-1)%PRIME"
    for (i = 0; i < patternLen - 1; i++)
        hashOfPatternLength = (hashOfPatternLength * TOTAL_CHARS) % PRIME;
    std::cout << "hashOfPatternLength : " << hashOfPatternLength << "\n";

    // Calculate the hash value of pattern and first
    // window of text
    std::cout << "patternHash calculation: \n";
    int temp = 0;
    int toInt = 0;
    for (i = 0; i < patternLen; i++)
    {
        temp = patternHash;
        toInt = pat[i];
        patternHash = (TOTAL_CHARS * patternHash + pat[i]) % PRIME;
        std::cout << "(" << TOTAL_CHARS << " * " << temp
                  << " + " << toInt << "[" << pat[i] << "]) % " << PRIME << " = "
                  << patternHash << "\n";
    }
    std::cout << "txtHash calculation: \n";
    for (i = 0; i < patternLen; i++)
    {
        temp = txtHash;
        toInt = txt[i];
        txtHash = (TOTAL_CHARS * txtHash + txt[i]) % PRIME;
        std::cout << "(" << TOTAL_CHARS << " * " << temp
                  << " + " << toInt << "[" << txt[i] << "]) % " << PRIME << " = "
                  << txtHash << "\n";
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= txtLen - patternLen; i++)
    {

        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters on by one
        if (patternHash == txtHash)
        {
            /* Check for characters one by one */
            for (j = 0; j < patternLen; j++)
            {
                if (txt[i + j] != pat[j])
                    break;
            }

            // if patternHash == txtHash and pat[0...patternLen-1] = txt[i, i+1, ...i+patternLen-1]
            if (j == patternLen)
            {
                cout << "Pattern found at index " << i << endl;
                return i;
            }
        }

        // Calculate hash value for next window of text: Remove
        // leading digit, add trailing digit
        if (i < txtLen - patternLen)
        {
            std::cout << "\nMoving the end index from " << i + patternLen - 1 << " to " << i + patternLen << "\n";
            temp = txtHash;
            toInt = txt[i];
            int toInt2 = txt[i + patternLen];
            txtHash = (TOTAL_CHARS * (txtHash - txt[i] * hashOfPatternLength) + txt[i + patternLen]) % PRIME;
            std::cout << "(" << TOTAL_CHARS << " * ("
                      << temp << " - " << toInt << "[" << txt[i] << "] * " << hashOfPatternLength << " ) + "
                      << toInt2 << "[" << txt[i + patternLen] << "] ) % " << PRIME << " = " << txtHash << "\n";
            // We might get negative value of txtHash, converting it
            // to positive
            if (txtHash < 0)
            {
                std::cout << "Negative hash created : " << txtHash;
                txtHash = (txtHash + PRIME);
                std::cout << ".  Hash updated to : " << txtHash << "\n";
            }
        }
    }
    return -1;
}

int main()
{
    string originalStr = "abcdefd";
    string patternStr = "bcde";
    // string originalStr = "ATErUUeUkVFVNfxfUKtntOErKmZLUpWpHRASdxjUhzzxygmnNnKabPPgPqyvCLSCZObaNNGCXQssfEEDDJIPBwtkMmTniKapBlrd";
    // string patternStr = "vCLSCZObaNNGCXQssfEEDDJIPBwtkMmTniKa";
    // int pos = searchPattern(originalStr, patternStr);
    std::cout << "originalStr : " << originalStr << "\npatternStr: " << patternStr << "\n";
    int pos = searchFirstOccurenceOfPattern(originalStr, patternStr);
    std::cout << "'" << patternStr << "' is found at pos " << pos << " in string '" << originalStr << "'";
    std::cin.get();
}