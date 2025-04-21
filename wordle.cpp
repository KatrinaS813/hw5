#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordle_helper(std::string& current, 
    const std::string& in, 
    std::string floating, 
    const std::set<std::string>& dict, 
    int index, 
    std::set<std::string>& results); 

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> results;
    string current = in; 
    wordle_helper(current, in, floating, dict, 0, results); 
    return results; 
}

// Define any helper functions here
void wordle_helper(std::string& current, 
    const std::string& in, 
    std::string floating, 
    const std::set<std::string>& dict, 
    int index, 
    std::set<std::string>& results) 
{
    if(index == (int)in.length()){
        if(floating.empty() && dict.find(current) != dict.end()){
            results.insert(current); 
        }
        return; 
    }
    if(in[index] != '-'){
        current[index] = in[index];
        wordle_helper(current, in, floating, dict, index+1, results); 
    } else {
        for(char c = 'a'; c <= 'z'; c++){
            current[index] = c; 
            size_t pos = floating.find(c);
            if(pos != string::npos){
                string updated = floating;
                updated.erase(pos, 1);
                wordle_helper(current, in, updated, dict, index+1, results);
            } else {
                int blanks = 0; 
                for(int i = index + 1; i < (int)in.length(); i++){
                    if (in[i] == '-'){
                        blanks++;
                    }
                }
                if((int)floating.length() <= blanks){
                    wordle_helper(current, in, floating, dict, index+1, results);
                }
            }
        }
    }
}
