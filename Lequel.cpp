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
#include <unordered_map>

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
                profile.insert(std::pair<string, float>(trigram, 1));

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
        pair.second = pair.second / sqrt(sumSquared);

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
    float cosineSimilarity = 0;
    int commonTrigrams = 0;
    int processed = 0;
    const float OVERLAP_THRESHOLD = 0.2f; //Superposicion minima para que se tenga en cuenta 

    for (auto &textPair : textProfile) 
    {
        processed++;
        TrigramProfile::iterator languagePair = languageProfile.find(textPair.first);

        if(languagePair != languageProfile.end())
        {
            cosineSimilarity += textPair.second * languageProfile[textPair.first];
            commonTrigrams++;
        }
        int remaining = textProfile.size() - processed;
        float maxPossibleOverlap = static_cast<float>(commonTrigrams + remaining) / textProfile.size();
        if(maxPossibleOverlap < OVERLAP_THRESHOLD)
        return 0;
    }

    float overlap = static_cast<float>(commonTrigrams) / textProfile.size();
    if(overlap < OVERLAP_THRESHOLD)
        return 0;

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
