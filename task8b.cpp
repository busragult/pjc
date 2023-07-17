#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
using namespace std;
struct Connection
{
    string from;
    string to;
    int duration;
    Connection(string from, string to, int duration)
        : from(from), to(to), duration(duration)
    {
    }
};
ostream &operator<<(ostream &s, const Connection &c)
{
    s << c.from << " -> " << c.to << ": " << c.duration << "s";
    return s;
}
int main()
{
    map<string, vector<Connection>> m;
    ifstream infile("STL-telephones.dat");

    // ...
    // reading data and inserting it into the map
    // ...
    string from, to;
    int duration;
    while (infile >> from >> to >> duration)
    {
        Connection connect{from, to, duration};
        m[from].push_back(connect);
    }

    infile.close();
    string chatterbox;   // name of greatest chatterbox
    int longestTime = 0; // longest time 'talked' by

    // one person as the caller
    // ...
    // loop calculating and printing total time
    // talked by each person and finding the person
    // with this time the longest
    // ...
    // printing the name and the list of
    // connections of the greatest chatterbox

    for (auto it = m.cbegin(); it != m.cend(); ++it)
    {
        std::cout << it->first << ": ";
        duration = 0;
        for (int i = 0; i < it->second.size(); i++)
            duration += it->second.at(i).duration;
        std::cout << duration << " seconds" << std::endl;
        if (longestTime < duration)
        {
            longestTime = duration;
            chatterbox = it->first;
        }
    }

    std::cout << chatterbox << " chattered for " << longestTime << " seconds in " << m[chatterbox].size() << " connections" << std::endl;

    for (int i = 0; i < m[chatterbox].size(); i++)
        std::cout << m[chatterbox].at(i) << std::endl;
}
