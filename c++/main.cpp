#include <iostream>
#include <fstream>
#include <unordered_map>

#define FILEPATH

using namespace std;

struct cityTemp {
    int min,max,sum,cnt;
    float avg;
};
unordered_map<string, cityTemp> mp;
void readFileAndBuildMap(){
    string str;
    ifstream filehandle( "../data/measurements-100M.txt");
    
    if(!filehandle.is_open()){
        cout << "FAILED to open";
        return;
    }
    while(getline(filehandle, str)){
        int i = str.find(';');
        string city_name = str.substr(0,i);
        string tempstr = str.substr(i+1);
        int j = tempstr.find('.');
        int temp = stoi(tempstr.substr(0, j)+tempstr.substr(j+1) );
        
        if(mp.find(city_name) == mp.end()){
            // not found
            mp.insert({city_name, {min: temp, max: temp, sum: temp, cnt: 1 }});

        }else{
            mp[city_name].min = min(mp[city_name].min, temp);
            mp[city_name].max = max(mp[city_name].max, temp);
            mp[city_name].sum += temp;
            mp[city_name].cnt++;
        }
    }
    filehandle.close();
}
int main(){
    time_t start, end; 
    time(&start);
    readFileAndBuildMap();
    ofstream outfile("./out.txt");
    for(auto t: mp){
        t.second.avg = (((float)(t.second.sum))/(float)(100*t.second.cnt));
        outfile <<  t.first << "=" << t.second.min/100.0 << "/" << t.second.avg << "/" << t.second.max/100.0 << "\n";
    }
    time(&end);
    double time_taken = double(end - start); 
    cout << "DONE in " << time_taken << " _ " << mp.size()<< endl;
}