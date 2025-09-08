/**
 * @brief Reads text files
 * @author Marc S. Ressl
 * 
 * @copyright Copyright (c) 2022-2023
 */

#include <fstream>

#include "Text.h"

using namespace std;

/**
 * @brief Converts a '\n'-separated string to a list of strings.
 *
 * @param s String to convert
 * @param text Destination text
 * @return Function succeeded
 */
bool getTextFromString(const string &s, Text &text)
{
    text.clear();

    string::size_type position = 0;
    string::size_type prevPosition = 0;
    while ((position = s.find('\n', prevPosition)) != string::npos)
    {
        if ((position > prevPosition) && (s[position - 1] == '\r'))
            text.push_back(s.substr(prevPosition, position - 1 - prevPosition));
        else
            text.push_back(s.substr(prevPosition, position - prevPosition));

        prevPosition = position + 1;
    }

    // To get the last substring (or only, if delimiter is not found)
    text.push_back(s.substr(prevPosition));

    return true;
}

/**
 * @brief Loads a text file as a list of strings.
 *
 * @param path Path of file to read
 * @param text Destination text
 * @return Function succeeded
 */
bool getTextFromFile(const string path, Text &text)
{
    ifstream file(path, ios::binary);

    if (!file.is_open())
    {
        perror(("Error while opening file " + path).c_str());
        return false;
    }

    // Get file size
    file.seekg(0, ios::end);
    int fileSize = file.tellg() > 10000000 ? 10000000 : (int)file.tellg();
    string fileData(fileSize, ' ');
    file.seekg(0);

    file.read(&fileData[0], fileSize);

    if (file.fail())
    {
        perror(("Error while reading file: " + path).c_str());
        return false;
    }

    file.close();

    return getTextFromString(fileData, text);
}
