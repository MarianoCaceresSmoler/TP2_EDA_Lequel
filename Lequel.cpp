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
#include <thread>
#include <mutex>
#include <vector>

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

            transform(trigram.begin(), trigram.end(), trigram.begin(), [](unsigned char c)
                      { return tolower(c); }); // lowercase the trigram

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

    for (auto &textPair : textProfile) 
    {
        auto languagePair = languageProfile.find(textPair.first);

        if (languagePair != languageProfile.end())
        {
            cosineSimilarity += textPair.second * languagePair->second;
        }
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

/**
 * @brief Identifies the language of a text using threads
 *
 * @param text A Text (vector of lines)
 * @param languages A list of Language objects
 * @return string The language code of the most likely language
 */
string identifyLanguageThreads (const Text &text, LanguageProfiles &languageProfiles)
{
    TrigramProfile textProfile = buildTrigramProfile(text);
    normalizeTrigramProfile(textProfile);

    float maxCosineSimilarity = 0;
    string languageCode = "---";
    std::mutex mtx;

    auto worker = [&](int start, int end){
        float localMax = 0;
        string localLang = "---";

        for (int i = start; i < end; i++) {
            auto &languageProfile = languageProfiles[i];
            float similarity = getCosineSimilarity(textProfile, languageProfile.trigramProfile);
            cout << "Cosine similarity: " << languageProfile.languageCode << " -> " << similarity << "\n";

            if (similarity > localMax) {
                localMax = similarity;
                localLang = languageProfile.languageCode;
            }
        }
        std::lock_guard<std::mutex> lock(mtx);
        if(localMax > maxCosineSimilarity)
        {
            maxCosineSimilarity = localMax;
            languageCode = localLang;
        }
    };

    int numThreads = std::thread::hardware_concurrency(); // detecta los nucleos del cpu
    int blockSize = (languageProfiles.size() + numThreads - 1) / numThreads;

    std::vector<std::thread> threads;
    for(int t = 0; t < numThreads; t++)
    {
        int start = t * blockSize;
        int end = std::min(start + blockSize, (int)languageProfiles.size());
        threads.emplace_back(worker, start, end);
    }

    for(auto &th : threads)
        th.join();

    return languageCode;
}