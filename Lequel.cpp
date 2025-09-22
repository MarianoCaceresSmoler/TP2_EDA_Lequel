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
#include <algorithm>
#include <cctype>
#include "Lequel.h"

#define MAX_TRIGRAMS 2000 // limit number of trigrams per text

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
        if (profile.size() >= MAX_TRIGRAMS) // Stop if limit is reached
            break;

        if ((line.length() > 0) && (line[line.length() - 1] == '\r'))
            line = line.substr(0, line.length() - 1);

        if (line.length() < 3) // kip line if it has less than three chars
            continue;

        wstring unicodeString = converter.from_bytes(line);

        // Iterate over all trigrams in the line
        for (int i = 0; i < unicodeString.length() - 2 && profile.size() <= MAX_TRIGRAMS; i++)
        {
            wstring unicodeTrigram = unicodeString.substr(i, 3);
            string trigram = converter.to_bytes(unicodeTrigram);

            // Lowercase the trigram
            transform(trigram.begin(), trigram.end(), trigram.begin(), [](unsigned char c)
                      { return tolower(c); }); 

            // Increment count or insert new trigram
            TrigramProfile::iterator pair = profile.find(trigram);
            if (pair != profile.end())
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

    // Get the sum of squares of frequencies
    for (const auto &pair : trigramProfile)
        sumSquared += pair.second * pair.second;

    // Divide each frequency by root of the number calculated
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
    const float OVERLAP_THRESHOLD = 0.2f; // Minimum of 20% of trigrams in common to continue

    for (auto &textPair : textProfile)
    {
        processed++;

        // Check if this trigram exists in the language profile
        TrigramProfile::iterator languagePair = languageProfile.find(textPair.first);
        if (languagePair != languageProfile.end())
        {
            cosineSimilarity += textPair.second * languageProfile[textPair.first];
            commonTrigrams++;
        }

        // Estimate maximum possible overlap if we continued
        size_t remaining = textProfile.size() - processed;
        float maxPossibleOverlap = static_cast<float>(commonTrigrams + remaining) / textProfile.size();

        // Stop early if threshold cannot be reached
        if (maxPossibleOverlap < OVERLAP_THRESHOLD)
            break;
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
    std::string languageCode = "---"; // default if no match

    // Compare against all language profiles
    for (auto &languageProfile : languageProfiles)
    {
        float similarity = getCosineSimilarity(textProfile, languageProfile.trigramProfile);
        cout << "Cosine similarity: " << languageProfile.languageCode << " -> " << similarity << std::endl;

        if (similarity > maxCosineSimilarity)
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
string identifyLanguageThreads(const Text &text, LanguageProfiles &languageProfiles)
{
    TrigramProfile textProfile = buildTrigramProfile(text);
    normalizeTrigramProfile(textProfile);

    float maxCosineSimilarity = 0;
    string languageCode = "---";
    std::mutex mtx; // to update information safely

    // Worker function executed by each thread
    auto worker = [&](int start, int end)
    {
        float localMax = 0;
        string localLang = "---";

        for (int i = start; i < end; i++)
        {
            auto &languageProfile = languageProfiles[i];
            float similarity = getCosineSimilarity(textProfile, languageProfile.trigramProfile);
            cout << "Cosine similarity: " << languageProfile.languageCode << " -> " << similarity << std::endl;

            if (similarity > localMax)
            {
                localMax = similarity;
                localLang = languageProfile.languageCode;
            }
        }

        // Merge thread-local result into global result
        std::lock_guard<std::mutex> lock(mtx);
        if (localMax > maxCosineSimilarity)
        {
            maxCosineSimilarity = localMax;
            languageCode = localLang;
        }
    };
    
    // Determine how many threads to use
    int numThreads = std::thread::hardware_concurrency();
    int blockSize = (languageProfiles.size() + numThreads - 1) / numThreads;

    std::vector<std::thread> threads;

    // Assign blocks to threads
    for (int t = 0; t < numThreads; t++)
    {
        int start = t * blockSize;
        int end = std::min(start + blockSize, (int)languageProfiles.size());
        threads.emplace_back(worker, start, end);
    }

    // Wait for all threads to finish
    for (auto &th : threads)
        th.join();

    cout << "Final: " << languageCode << std::endl;

    return languageCode;
}