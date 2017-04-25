//
//  main.cpp
//  CSCI 2421 Homework 8
//
//  Created by Bradley Ruck on 4/23/16.
//  Copyright © 2016 Bradley Ruck. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

const int maxBuckets = 1373; // Target bucket count

ifstream& getWord(ifstream& testFile, string& testWord);

int main() {

    unordered_set<string> dictHashTable;
    string dictWord;
    string word;
    string fileName;
    int maxBucketRatio = 25000/maxBuckets; // 25k est number of words in dictionary
    int countMisspelled = 0;
    int countCorrect = 0;

    // Get input of words for dictionary
    ifstream dictionary("dict.txt");

    if (dictionary.fail()){
        cout << "There is a problem with the dictionary data file" << endl;
    }
    else{
        // Create the dictionary as a hash table while limiting number of buckets
        dictHashTable.max_load_factor(maxBucketRatio);
        while(dictionary >> dictWord){
            dictHashTable.emplace(dictWord);
        }
    }
    dictionary.close();

    // Get input file name from user
    cout << "\nPlease enter the name and path of the file you would like to spell check: ";
    getline(cin, fileName);
    ifstream input(fileName);
    cout << endl;

    if (input.fail()){
        cout << "\nFile does not exist or path is wrong" << endl;
    }
    cout << "LIST OF MISSPELLED WORDS: " << endl;

    // If a word is not in the dictionary assume it is misspelled
    while(input){
        getWord(input, word);
        if(word != ""){
            auto search = dictHashTable.find(word);
            if(search == dictHashTable.end()){
                cout << "  " << word << endl;
                countMisspelled++; // Increment misspelled count
            }
            else{
                countCorrect++; // Increment correctly spelled count
            }
        }
    }
    input.close();

    cout << endl;
    cout << "Number of misspelled words: " << countMisspelled << endl;
    cout << "Number of correctly spelled words: " << countCorrect << endl;
    cout << "Bucket count: " << dictHashTable.bucket_count() << endl << endl;

    return 0;
}

// Function to clear punctuation, numbers and spaces then convert to lower case
ifstream& getWord(ifstream& testFile, string& testWord){

    char c;

    // Clear the string of characters
    testWord = "";

    // Do nothing, ignore c if not a letter
    while (testFile.get(c) && !isalpha(c));

    // Return on end-of-line
    if(testFile.eof())
        return testFile;

    // Record first letter of the word
    testWord += tolower(c);

    // Collect letters, ignore punctuation and digits
    while (testFile.get(c) && (isalpha(c)))
        testWord += tolower(c);

    return testFile;
}