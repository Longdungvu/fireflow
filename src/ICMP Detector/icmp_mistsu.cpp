#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <math.h>

using namespace std;

struct ICMPPacket {
    int    packetNum;
    string srcIP;
    string dstIP;
    string protocol;
    int    packetLen;
};

inline ICMPPacket* getPacket(string line) {
    ICMPPacket* ppacket = new ICMPPacket;
    int         stage   = 0;
    int         i       = 0;

    string arg;
    while (i < (int)line.length()) {
        // Get argument seperated by ' '
        arg = "";
        while (i < (int)line.length() && line[i] != ' ')
            arg += line[i++];
        i++;

        // Add argument to struct
        // if (stage == 0) ppacket->packetNum = atoi(&arg[0]);
        // if (stage == 1) ppacket->srcIP     = arg;
        // if (stage == 3) ppacket->dstIP     = arg;
        // if (stage == 5) ppacket->protocol  = arg;
        // if (stage == 7) ppacket->packetLen = atoi(&arg[0]);

        if (stage == 0) ppacket->srcIP     = arg;
        if (stage == 2) ppacket->dstIP     = arg;
        if (stage == 4) ppacket->protocol  = arg;
        if (stage == 6) ppacket->packetLen = atoi(&arg[0]);

        // Increase stage of getting argument
        stage++;
    }

    // The log file gets broken if no of arguments < 8
    // return (stage >= 8 ? ppacket : NULL);
    return (stage >= 7 ? ppacket : NULL);
}
//print the packet
// void printPacketNicely(ICMPPacket* ppacket) {
//     if (!ppacket)
//         return;
//
//     cout << "#########################################" << endl;
//     cout << "[] Packet number : " << ppacket->packetNum << endl;
//     cout << "[] Source IP     : " << ppacket->srcIP     << endl;
//     cout << "[] Destination IP: " << ppacket->dstIP     << endl;
//     cout << "[] Protocol      : " << ppacket->protocol  << endl;
//     cout << "[] Packet length : " << ppacket->packetLen << endl;
// }

// calculate entropy for detection
void countEntropy() {

}
// dynamic array of srcIP
map<string, double> probSrcIP;
vector<string>      srcIPlist;
int                 windowsSize = 1000;
int main() {
    // Open file
    fstream logfile;
    logfile.open("packkk.txt", fstream::in);

    // Get line-by-line
    string line;
    while (getline(logfile, line)) {
        ICMPPacket* ppacket = getPacket(line);
        // array of all srcIP
        if (ppacket)
            srcIPlist.push_back(ppacket->srcIP);
        // printPacketNicely(ppacket);
    }

    for (int i = 0; i < srcIPlist.size(); i++) {
        if (probSrcIP.count(srcIPlist[i]) == 0) {
            probSrcIP[srcIPlist[i]]  = 1.0 / windowsSize;
        } else {
            probSrcIP[srcIPlist[i]] += 1.0 / windowsSize;
        }

        if (i >= windowsSize) {
            probSrcIP[srcIPlist[i - windowsSize]] -= 1.0 / windowsSize;

            double entropy = 0;
            for (map<string, double>::iterator it = probSrcIP.begin(); it != probSrcIP.end(); it++) {
                if (it->second != 0)
                    entropy += it->second * log2(it->second);
            }

            cout << "entropy is " << entropy << "\n";
        }
    }

}
