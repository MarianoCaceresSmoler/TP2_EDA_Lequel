/**
 * @brief Lequel    ? language identification based on trigrams
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 *
 * @cite https://towardsdatascience.com/understanding-cosine-similarity-and-its-application-fd42f585296a
 */

#include <cmath>
#include <codecvt>
#include <locale>
#include <iostream>
#include <map>

#include "Lequel.h"

using namespace std;

/**
 * @brief Builds a trigram profile from a given text.
 *
 * @param text Vector of lines (Text)
 * @return TrigramProfile The trigram profile
 */
TrigramProfile buildTrigramProfile(const Text &text)
{
    wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    // Your code goes here...
    TrigramProfile profile;
    for (auto line : text)
    {
        if ((line.length() > 0) && (line[line.length() - 1] == '\r'))
            line = line.substr(0, line.length() - 1);

        if (line.length() < 3)
            continue;

        wstring unicodeString = converter.from_bytes(line);

        for(int i = 0; i < unicodeString.length() - 2; i++)
        {
            wstring unicodeTrigram = unicodeString.substr(i, 3);
            string trigram = converter.to_bytes(unicodeTrigram);

            TrigramProfile::iterator pair = profile.find(trigram);

            if(pair != profile.end())
                profile[trigram] += 1.0F;
            else
                profile.insert(std::pair<string, float>(trigram, 0));
        }      
    
    }

    return profile;
}

/**
 * @brief Normalizes a trigram profile.
 *
 * @param trigramProfile The trigram profile.
 */
void normalizeTrigramProfile(TrigramProfile &trigramProfile)
{
    float sumSquared = 0;
    for (const auto &pair : trigramProfile) 
        sumSquared += pair.second * pair.second;

    for (auto &pair : trigramProfile) 
        pair.second /= sqrt(sumSquared);

}

/**
 * @brief Calculates the cosine similarity between two trigram profiles
 *
 * @param textProfile The text trigram profile
 * @param languageProfile The language trigram profile
 * @return float The cosine similarity score
 */
float getCosineSimilarity(TrigramProfile &textProfile, TrigramProfile &languageProfile)
{
    // Your code goes here...

    float cosineSimilarity;

    for (auto &textPair : textProfile) 
    {
        TrigramProfile::iterator languagePair = languageProfile.find(textPair.first);

        if(languagePair != languageProfile.end())
            cosineSimilarity += textPair.second + languageProfile[textPair.first];
    }

    return cosineSimilarity;
}

/**
 * @brief Identifies the language of a text.
 *
 * @param text A Text (vector of lines)
 * @param languages A list of Language objects
 * @return string The language code of the most likely language
 */
string identifyLanguage(const Text &text, LanguageProfiles &languageProfiles)
{
    // Your code goes here...
    TrigramProfile textProfile = buildTrigramProfile(text);
    normalizeTrigramProfile(textProfile);

    float maxCosineSimilarity = 0;
    std::string languageCode = "---";

    for(auto &languageProfile : languageProfiles)
    {
        float similarity = getCosineSimilarity(textProfile, languageProfile.trigramProfile);
        if(similarity > maxCosineSimilarity)
        {
            maxCosineSimilarity = similarity;
            languageCode = languageProfile.languageCode;
        }
    }

    return languageCode;
}
