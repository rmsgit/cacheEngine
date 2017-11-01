#include <iostream>
#include <thread>
#include <atomic>
#include <afxres.h>
#include "cacheStore.h"

#define ADD 1
#define GET 2

using namespace std;
using namespace CacheStore;



int main() {
    CacheRow cacheRow;
    cacheRow.init(5);
    CacheRow Queue;
    Queue.init(5);


    while (1) {

        cout << ">";
        string input = "";
        cin >> input;

        if (input == "exit") {

            break;
        } else if (input == "add") {
            int ref;
            cin >> ref;
            cin >> input;
            Block block;
            block.value = input;
            block.ref = ref;
            block.attempt = 0;
            /*Queue->addBlock(block);

            if (!QueueCleanThread.joinable()) {
                QueueCleanThread.detach();
            }
            QueueCleanThread.join();*/

            if (Queue.hasHadata(ref) == -1) {
                //Queue.addBlock(block);


                thread threadAddBlock(Queue.addBlock, Queue, block);
                threadAddBlock.join();

            } else {
                thread threadAddBlock(cacheRow.addBlock, cacheRow, block);
                thread threadRemoveBlock(Queue.removeBlock, Queue, ref);
                threadAddBlock.join();
                threadRemoveBlock.join();

                Queue.removeBlock(ref);

            }

        } else if (input == "remove") {
            int ref;
            cin >> ref;
            cacheRow.removeBlock(ref);
            cacheRow.viewAll();
        } else if (input == "all") {
            cout << "Queue" << endl;
            Queue.viewAll();
            cout << "Cache" << endl;
            cacheRow.viewAll();
        }

    }
    return 0;
}
