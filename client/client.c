#include "../cs_network.h"
#include <unistd.h>

int main(int argc, const char** argv){
    sleep(3);
    client cs_client;

    cs_client.init = init_client;

    cs_client.init(&cs_client);

    return 0;
}