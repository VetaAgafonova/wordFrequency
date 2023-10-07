#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	string word;
	const string fileName = "C://Users//super//eclipse-workspace//wordFrequency//src//Alice's Adventures in Wonderland.txt";
	const unsigned short n = 20; //[0, 65535]
	unordered_map<string, unsigned int> freqs;

	fstream fin(fileName);
	if(!fin){
		cout << "Error opening file " << fileName << endl;
		return 1;
	}
	if(fin.peek() == ifstream::traits_type::eof()){
		cout << "File " << fileName << "is empty\n";
		return 1;
	}

	while (fin >> word){
		auto it = remove_if(word.begin(), word.end(), ::ispunct);
		word.erase(it, word.end());
		transform(word.begin(), word.end(), word.begin(), ::tolower);
		++freqs[word];
	}

	if(n > freqs.size()){
		cout << "N more than words in the text\n";
		return 1;
	}

	vector<pair<string, unsigned int>> sortedFreqs(freqs.begin(),freqs.end());
	sort(sortedFreqs.begin(), sortedFreqs.end(),
		[](const auto& p1, const auto& p2){return tie(p2.second, p1.first) < tie(p1.second, p2.first);});

	for (int i = 0; i < n; i++)
	    cout << "№" << i+1 << "\t" << sortedFreqs[i].second << "\t" << sortedFreqs[i].first << endl;

	return 0;
}
