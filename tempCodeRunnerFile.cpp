#include <unordered_map>
#include <vector>
using namespace std;

vector<int> getUnexpired(int timeToLive, vector<string> queries) {
    vector<int> results;
    unordered_map<string, int> mp;
    
    for (string query : queries) {
        int space_idx = query.find(" ");
        string query_type = query.substr(0, space_idx);
        string remaining_query = query.substr(space_idx + 1);
        
        if (query_type == "generate") {
            int space_idx2 = remaining_query.find(" ");
            string tokenId = remaining_query.substr(0, space_idx2);
            int currentTime = stoi(remaining_query.substr(space_idx2 + 1));
            mp[tokenId] = currentTime + timeToLive;
        } 
        
        else if (query_type == "renew") {
            int space_idx2 = remaining_query.find(" ");
            string tokenId = remaining_query.substr(0, space_idx2);
            int currentTime = stoi(remaining_query.substr(space_idx2 + 1));

            if (mp[tokenId] > currentTime) {
                mp[tokenId] = currentTime + timeToLive;
            } 
            else {
                mp[tokenId] = 0;
            }

        } 
        
        else if (query_type == "count") {
            int currentTime = stoi(remaining_query);
            int count = 0;
            for (auto x : mp) {
                if (x.second > currentTime) {
                    count++;
                }
            }
            results.push_back(count);
        }
    }
    
    return results;
}

int main(){
    vector<string> queries;
    queries={"generate token1 3", "count 4", "generate token2 6", "count 7", "generate token3 11", "count 41"};

    vector<int> result = getUnexpired(35,queries) ;

    for(auto it:results){
        cout<<it<<" ";
    }
    return 0;
}