/*
Given a string s, find the length of the longest substring without duplicate characters.
*/

class Solution {
    public:
        int lengthOfLongestSubstring(string s) {
                std::vector<char> used={}; 
                int maxLength = 0; 
                for(int i = 0; i < s.length(); i++) { 
                    for(int j = 0; j < used.size(); j++) { //loop for checking if the character was in used
                        if(s[i] == used[j]) { 
                            used.erase(used.begin(), used.begin() + j + 1);
                            break; 
                        }
                    }
                    used.push_back(s[i]); 
                    maxLength = std::max(maxLength, (int)used.size());
                }
                return maxLength; 
            }
    };