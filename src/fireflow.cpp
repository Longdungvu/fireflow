#include <string>
#include <CLI11.hpp>
#include "capture.h"
#include "parser.h"

using namespace std;

string interface = "";
string logfile_path = "/tmp/fireflow/pfring_init.log";
string packet_file = "/tmp/packetlogger.txt";

int main(int argc, char* argv[]){
    CLI::App app{"FIREFLOW: USTH ANTI_DDOS"};

    std::string filename ;
    app.add_option("-i,--interface", interface, "Capture interface")->required();
    app.add_option("-l", logfile_path, "Dump to log file");
    
    CLI11_PARSE(app, argc, argv);
    
    init_logging();
    start_pfring_capture();
    
}