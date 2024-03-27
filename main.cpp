#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <set>

using namespace std;

int main()
{
    unordered_map<int, string> lookupMap;
    unordered_map<string, vector<int>> deleteMap;

    // Open files
    ifstream input("reviewers.in");
    ofstream output("reviewers.out");

    string line;
    while (getline(input, line))
    {
        istringstream iss(line);
        string action;
        iss >> action;

        if (action == "I")
        {
            string reviewerName;
            bool isUsed = false;
            bool limitReached = false;
            int num;
            set<int> nums;
            int numCount;

            iss >> reviewerName;
            iss >> numCount;

            if (deleteMap[reviewerName].size() == 50)
            {
                output << "no" << endl;
                continue;
            }

            while (iss >> num)
            {
                nums.insert(num);
            }

            for (auto it = nums.begin(); it != nums.end();)
            {
                auto x = *it;
                if (lookupMap.find(x) != lookupMap.end())
                {
                    if (lookupMap[x] != reviewerName)
                    {
                        isUsed = true;
                        break;
                    }
                    it = nums.erase(it);
                    continue;
                }
                ++it;
            }

            if (isUsed)
            {
                output << "no" << endl;
                continue;
            }

            for (auto &x : nums)
            {
                if (deleteMap[reviewerName].size() == 50)
                {
                    break;
                }
                lookupMap[x] = reviewerName;
                deleteMap[reviewerName].push_back(x);
            }
            if (deleteMap[reviewerName].size() <= 50)
            {
                output << "ok" << endl;
            }
            else
            {
                output << "no" << endl;
            }
        }
        else if (action == "L")
        {
            int lookupNum;
            iss >> lookupNum;

            if (lookupMap.find(lookupNum) == lookupMap.end())
            {
                output << "no" << endl;
            }
            else
            {
                output << lookupMap[lookupNum] << endl;
            }
        }
        else if (action == "D")
        {
            int deleteNum;
            string deleteName;
            iss >> deleteNum;

            if (lookupMap.find(deleteNum) == lookupMap.end())
            {
                output << "no" << endl;
                continue;
            }

            deleteName = lookupMap[deleteNum];
            for (int i = 0; i < deleteMap[deleteName].size(); i++)
            {
                lookupMap.erase(deleteMap[deleteName][i]);
            }
            deleteMap.erase(deleteName);

            output << "ok" << endl;
        }
    }

    input.close();
    output.close();
    return 0;
}