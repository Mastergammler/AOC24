#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;

vector<string> split_all(const char* input, char sep, bool skipEmpty = true)
{
    vector<string> splits;

    int idx = 0;
    int prevIdx = 0;
    const char* c = input;

    while (idx < INT_MAX)
    {
        if (*c == sep || *c == '\0')
        {
            int length = idx - prevIdx;

            // TODO: i allocate this here but never deallocate it
            // - so a new one for every string.split call
            char* substr = new char[length + 1];
            for (int i = 0; i < length; i++)
            {
                substr[i] = input[prevIdx + i];
            }
            // without the null terminator, we'll get problems while printing
            substr[length] = '\0';

            // NOTE: since this is a string vector, it will
            // allocate new memory here for the array also
            // using vector<char*> would eleviate the problem,
            // but then we would need to handle null
            // termination ourselfes, so we keep it that way

            if (!skipEmpty || length > 0)
            {
                splits.push_back(substr);
            }
            prevIdx = idx + 1;
        }

        // TODO: pretty ugly -> refactor
        if (*c == '\0') break;

        c++;
        idx++;
    }

    return splits;
}

int main(int argc, char* argv[])
{
    if (argc < 2) return 1;

    const char* fileName = argv[1];
    FILE* file = fopen(fileName, "r");
    if (file == NULL)
    {
        cerr << "Unabe to open file: " << fileName << endl;
        return 1;
    }

    string fullText;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        fullText.append(buffer);
    }

    vector<string> lines = split_all(fullText.c_str(), '\n');

    int safeReports = 0;

    for (int i = 0; i < lines.size(); i++)
    {
        string curLine = lines[i];
        vector<string> numStrings = split_all(curLine.c_str(), ' ');

        bool isSafeReport = true;
        bool lastAscending = true;

        for (int n = 0; n < numStrings.size() - 1; n++)
        {
            int curNum = atoi(numStrings[n].c_str());
            int nextNum = atoi(numStrings[n + 1].c_str());

            int delta = nextNum - curNum;
            int diff = abs(delta);

            if (diff > 3 || diff == 0)
            {
                isSafeReport = false;
                break;
            }

            bool currentAscending = delta > 0;

            // skip additional check the first time
            if (n > 0 && currentAscending != lastAscending)
            {
                isSafeReport = false;
                break;
            }

            lastAscending = currentAscending;
        }

        if (isSafeReport) safeReports++;
    }

    cout << "Evaluated " << lines.size() << " lines, found " << safeReports
         << " safe reports" << endl;
    fclose(file);

    return 0;
}
