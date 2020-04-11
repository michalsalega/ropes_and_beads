// Michal Salega
#include <iostream>
using namespace std;

struct Bead {
    int id;
    char ropeID1;
    char ropeID2;
    char ropeID3;
    Bead* nextBead;
    Bead* nextLink; // next link

    Bead(int id, char ropeID1, char ropeID2, char ropeID3) {
        this->id = id;
        this->ropeID1 = ropeID1;
        this->ropeID2 = ropeID2;
        this->ropeID3 = ropeID3;
        this->nextBead = NULL;
        this->nextLink = NULL;
    }

    bool hasNext() {

        return this->nextBead != NULL;
    }

    bool hasNextLink() {

        return this->nextLink != NULL;
    }

    int compareBeads(Bead* beadToCompare) {

        char bead1char1 = this->ropeID1;
        char bead1char2 = this->ropeID2;
        char bead1char3 = this->ropeID3;

        char bead2char1 = beadToCompare->ropeID1;
        char bead2char2 = beadToCompare->ropeID2;
        char bead2char3 = beadToCompare->ropeID3;

        if(bead1char1 == bead2char1 && bead1char2 == bead2char2 && bead1char3 == bead2char3 && this->id == beadToCompare->id) {
            return 0;
        } else if((bead1char1 > bead2char1) || (bead1char1 == bead2char1 && bead1char2 > bead2char2) ||
                (bead1char1 == bead2char1 && bead1char2 == bead2char2 && bead1char3 > bead2char3) ||
                (bead1char1 == bead2char1 && bead1char2 == bead2char2 && bead1char3 == bead2char3 && this->id > beadToCompare->id)) {

            return -1;
        } else {
            return 1;
        }
    }

    void addNewLink(Bead* newLink) {

        Bead* newLinkToInsert = new Bead(newLink->id, newLink->ropeID1, newLink->ropeID2, newLink->ropeID3);

        if(this->nextLink == NULL) {
            this->nextLink = newLinkToInsert;
            return;
        } else {

            Bead* currLinkedBead = this->nextLink;

            if(currLinkedBead->compareBeads(newLinkToInsert) == -1) {

                newLinkToInsert->nextLink = currLinkedBead;
                this->nextLink = newLinkToInsert;
                return;
            }

            while(currLinkedBead->hasNextLink()) {

                Bead* nextLinkedBead = currLinkedBead->nextLink;

                if(nextLinkedBead->compareBeads(newLinkToInsert) == -1) {

                    newLinkToInsert->nextLink = nextLinkedBead;
                    currLinkedBead->nextLink = newLinkToInsert;

                    return;
                }

                currLinkedBead = currLinkedBead->nextLink;
            }

            currLinkedBead->nextLink = newLinkToInsert;

            return;
        }
    }

    void deleteLink(Bead* beadToDelete) {

        Bead* currLink = this->nextLink;

        if(currLink != NULL) {
            if(currLink->compareBeads(beadToDelete) == 0) {
                this->nextLink = currLink->nextLink;
                delete(currLink);
                return;
            }

            Bead* currLink = this->nextLink;
            if(currLink != NULL) {
                while(currLink->hasNextLink()) {

                    Bead* currLinkNext = currLink->nextLink;

                    if(currLinkNext->compareBeads(beadToDelete) == 0) {

                        currLink->nextLink = currLinkNext->nextLink;
                        delete(currLinkNext);
                        return;
                    }

                    currLink = currLink->nextLink;
                }
            }
        }
    }
};

struct Rope {
    char id1;
    char id2;
    char id3;
    Bead* firstBead;
    Rope* nextRope;

    Rope(char id1, char id2, char id3) {
        this->id1 = id1;
        this->id2 = id2;
        this->id3 = id3;
        this->firstBead = NULL;
        this->nextRope = NULL;
    }

    bool hasNext() {

        return this->nextRope != NULL;
    }

    int compareRopes(Rope* ropeToCompare) {

        char rope1char1 = this->id1;
        char rope1char2 = this->id2;
        char rope1char3 = this->id3;

        char rope2char1 = ropeToCompare->id1;
        char rope2char2 = ropeToCompare->id2;
        char rope2char3 = ropeToCompare->id3;

        if(rope1char1 == rope2char1 && rope1char2 == rope2char2 && rope1char3 == rope2char3) {
            return 0;
        } else if((rope1char1 > rope2char1) || (rope1char1 == rope2char1 && rope1char2 > rope2char2) ||
                    (rope1char1 == rope2char1 && rope1char2 == rope2char2 && rope1char3 > rope2char3)) {

            return -1;
        } else {
            return 1;
        }
    }

    int compareRopesByID(char ropeToCompareID1, char ropeToCompareID2, char ropeToCompareID3) {

        char rope1char1 = this->id1;
        char rope1char2 = this->id2;
        char rope1char3 = this->id3;

        if(rope1char1 == ropeToCompareID1 && rope1char2 == ropeToCompareID2 && rope1char3 == ropeToCompareID3) {
            return 0;
        } else if((rope1char1 == ropeToCompareID1 && rope1char2 == ropeToCompareID2 && rope1char3 > ropeToCompareID3) ||
                  (rope1char1 == ropeToCompareID1 && rope1char2 > ropeToCompareID2) ||
                  (rope1char1 > ropeToCompareID1)) {
            return -1;
        } else {
            return 1;
        }
    }

    void addNewBead(Bead* newBead) {
        if(this->firstBead == NULL) { // nie musze ifa narazie zostawiam
            firstBead = newBead;
        } else {

            Bead* currBead = firstBead;

            if(currBead->id > newBead->id) {

                newBead->nextBead = firstBead;
                firstBead = newBead;
                return;
            }


            while (currBead->hasNext()) {

                Bead* nextBead = currBead->nextBead;

                if(nextBead->id > newBead->id) {

                    currBead->nextBead = newBead;
                    newBead->nextBead = nextBead;
                    return;
                }

                currBead = currBead->nextBead;
            }

            currBead->nextBead = newBead;

            return;
        }
    }

    Bead* getBead(int beadID) {

        Bead* currBead = firstBead;

        if(currBead->id == beadID) {
            return currBead;
        }

        while(currBead->hasNext()) {
            if(currBead->id == beadID) {
                return currBead;
            }
            currBead = currBead->nextBead;
        }

        if(currBead->id == beadID) {
            return currBead;
        }

        return NULL;
    }

    void deleteBead(Bead* beadToDelete) {

        Bead* currBead = firstBead;
        int beadToDeleteID = beadToDelete->id;

        if(currBead->id == beadToDeleteID) {
            Bead* nextLink = currBead->nextLink;

            while(currBead->nextLink != NULL) {
                Bead* currLink = currBead->nextLink;

                currBead->deleteLink(currLink);
            }

            firstBead = currBead->nextBead;
            delete(currBead);
            return;
        }

        while(currBead->hasNext()) {

            Bead* nextBead = currBead->nextBead;

            if(nextBead->id == beadToDeleteID) {

                while(nextBead->nextLink != NULL) {
                    Bead* currLink = nextBead->nextLink;

                    currBead->deleteLink(currLink);
                }

                currBead->nextBead = nextBead->nextBead;
                delete(nextBead);

                return;
            }

            currBead = currBead->nextBead;
        }
    }

};

struct Construction {
    Rope* firstRope;

    Construction() {
        this->firstRope = NULL;
    }

    void addRope(Rope* newRope) {
        if(this->firstRope == NULL) {
            this->firstRope = newRope;
        } else {

            Rope* currRope = firstRope;

            if(currRope->compareRopes(newRope) < 1) {

                newRope->nextRope = firstRope;
                firstRope = newRope;
                return;
            }

            while (currRope->hasNext()) {

                Rope* nextRope = currRope->nextRope;

                if(nextRope->compareRopes(newRope) < 1) {

                    newRope->nextRope = nextRope;
                    currRope->nextRope = newRope;
                    return;
                }

                currRope = currRope->nextRope;
            }

            currRope->nextRope = newRope;

            return;
        }
    }

    Rope* getRope(char ropeID1, char ropeID2, char ropeID3) {

        Rope* currRope = firstRope;

        if(currRope->compareRopesByID(ropeID1, ropeID2, ropeID3) == 0) {
            return currRope;
        }

        while(currRope->hasNext()) {

            Rope* nextRope = currRope->nextRope;

            if(nextRope->compareRopesByID(ropeID1, ropeID2, ropeID3) == 0) {
                return nextRope;
            }

            currRope = currRope->nextRope;
        }

        if(currRope->compareRopesByID(ropeID1, ropeID2, ropeID3) == 0) {
            return currRope;
        }

        return NULL;
    }

    void deleteAllLinksToBead(Bead* beadLinkToDelete) {

        Rope* currRope = firstRope;

        if(currRope != NULL) {

            Bead* currBead = currRope->firstBead;

            if(currBead != NULL) {

                Bead* currLink = currBead->nextLink;

                if(currLink != NULL) {

                    if(currLink->compareBeads(beadLinkToDelete) == 0) {
                        currBead->deleteLink(beadLinkToDelete);
                    }

                    Bead* currLink = currBead->nextLink;

                    if(currLink != NULL) {

                        while(currLink->hasNextLink()) {
                            Bead* nextLink = currLink->nextLink;

                            if(nextLink->compareBeads(beadLinkToDelete) == 0) {

                                currBead->deleteLink(nextLink);
                            }

                            currLink = currLink->nextLink;
                        }
                    }
                }

                while(currBead->hasNext()) {
                    Bead* nextBead = currBead->nextBead;

                    currLink = nextBead->nextLink;

                    if(currLink != NULL) {

                        if(currLink->compareBeads(beadLinkToDelete) == 0) {
                            nextBead->deleteLink(currLink);
                        }// check if null

                        Bead* currLink = nextBead->nextLink;

                        if(currLink != NULL) {
                            while(currLink->hasNextLink()) {
                                Bead* nextLink = currLink->nextLink;

                                if(nextLink->compareBeads(beadLinkToDelete) == 0) {

                                    nextBead->deleteLink(nextLink);
                                }

                                currLink = currLink->nextLink;
                            }
                        }

                    }

                    currBead = currBead->nextBead;
                }

            }

            while(currRope->hasNext()) {

                Rope* nextRope = currRope->nextRope;

                Bead* currBead = nextRope->firstBead;

                if(currBead != NULL) {

                    Bead* currLink = currBead->nextLink;

                    if(currLink != NULL) {

                        if(currLink->compareBeads(beadLinkToDelete) == 0) {
                            currBead->deleteLink(currLink);
                        }

                        Bead* currLink = currBead->nextLink;

                        if(currLink != NULL) {
                            while(currLink->hasNextLink()) {
                                Bead* nextLink = currLink->nextLink;

                                if(nextLink->compareBeads(beadLinkToDelete) == 0) {

                                    currBead->deleteLink(beadLinkToDelete);
                                }

                                currLink = currLink->nextLink;
                            }
                        }
                    }

                    while(currBead->hasNext()) {
                        Bead* nextBead = currBead->nextBead;

                        Bead* currLink = nextBead->nextLink;

                        if(currLink != NULL) {

                            if(currLink->compareBeads(beadLinkToDelete) == 0) {
                                nextBead->deleteLink(currLink);
                            }

                            Bead* currLink = nextBead->nextLink;

                            if(currLink != NULL) {
                                while(currLink->hasNextLink()) {
                                    Bead* nextLink = currLink->nextLink;

                                    if(nextLink->compareBeads(beadLinkToDelete) == 0) {

                                        nextBead->deleteLink(nextLink);
                                    }

                                    currLink = currLink->nextLink;
                                }
                            }

                        }

                        currBead = currBead->nextBead;
                    }

                }

                currRope = currRope->nextRope;
            }

        }

    }

    void relocateBead(Bead* beadToRelocate, Rope* ropeFrom, Rope* ropeTo) {

        Rope* currRope = this->firstRope;

        if(currRope->compareRopes(ropeFrom) == 0) {

            Bead* currBead = currRope->firstBead;

            if(currBead->compareBeads(beadToRelocate) == 0) {

                currRope->firstBead = currBead->nextBead;
            }

            while(currBead->hasNext()) {

                Bead* nextBead = currBead->nextBead;

                if(nextBead->compareBeads(beadToRelocate) == 0) {
                    currBead->nextBead = nextBead->nextBead;
                }

                if(currBead->hasNext()) {
                    currBead = currBead->nextBead;
                }
            }
        }

        while(currRope->hasNext()) {
            Rope* nextRope = currRope->nextRope;

            if(nextRope->compareRopes(ropeFrom) == 0) {

                Bead* currBead = nextRope->firstBead;

                if(currBead->compareBeads(beadToRelocate) == 0) {

                    nextRope->firstBead = currBead->nextBead;

                }

                while(currBead->hasNext()) {

                    Bead* nextBead = currBead->nextBead;

                    if(nextBead->compareBeads(beadToRelocate) == 0) {
                        currBead->nextBead = nextBead->nextBead;
                    }

                    if(currBead->hasNext()) {
                        currBead = currBead->nextBead;
                    }
                }
            }

            currRope = currRope->nextRope;
        }

        // wziety ale nie dany

        beadToRelocate->ropeID1 = ropeTo->id1;
        beadToRelocate->ropeID2 = ropeTo->id2;
        beadToRelocate->ropeID3 = ropeTo->id3;
        beadToRelocate->nextBead = NULL;

        ropeTo->addNewBead(beadToRelocate);
    }

    void deleteRope(Rope* ropeToDelete) {

        if(this->firstRope->compareRopes(ropeToDelete) == 0) {

            this->firstRope = this->firstRope->nextRope;

            delete(ropeToDelete);
            return;
        }

        Rope* currRope = this->firstRope;

        if(currRope != NULL) {
            while(currRope->hasNext()) {

                Rope* nextRope = currRope->nextRope;

                if(nextRope->compareRopes(ropeToDelete) == 0) {

                    currRope->nextRope = nextRope->nextRope;
                    delete(nextRope);
                    return;
                }

                currRope = currRope->nextRope;
            }
        }

    }

    void displayAll() {

        Rope* currRope = firstRope;

        //////////////////
        if(currRope != NULL) {
                cout << currRope->id1 << currRope->id2 << currRope->id3 << endl;

                Bead* currBead = currRope->firstBead;

                if(currBead != NULL) {
                    cout << currBead->id << " ";

                    Bead* currLink = currBead->nextLink;

                    if(currLink != NULL) {
                        cout << currLink->ropeID1 << currLink->ropeID2 << currLink->ropeID3 << " " << currLink->id << " ";

                        while(currLink->hasNextLink()) {
                            Bead* nextLink = currLink->nextLink;

                            cout << nextLink->ropeID1 << nextLink->ropeID2 << nextLink->ropeID3 << " " << nextLink->id << " ";

                            currLink = currLink->nextLink;
                        }
                    }

                    cout << endl;

                    while(currBead->hasNext()) {
                        Bead* nextBead = currBead->nextBead;

                        cout << nextBead->id << " ";

                        currLink = nextBead->nextLink;

                        if(currLink != NULL) {
                            cout << currLink->ropeID1 << currLink->ropeID2 << currLink->ropeID3 << " " << currLink->id << " ";

                            while(currLink->hasNextLink()) {
                                Bead* nextLink = currLink->nextLink;

                                cout << nextLink->ropeID1 << nextLink->ropeID2 << nextLink->ropeID3 << " " << nextLink->id << " ";

                                currLink = currLink->nextLink;
                            }
                        }

                        currBead = currBead->nextBead;
                        cout << endl;
                    }
                }

            while(currRope->hasNext()) {
                Rope* nextRope = currRope->nextRope;

                cout << nextRope->id1 << nextRope->id2 << nextRope->id3 << endl;

                currBead = nextRope->firstBead;

                if(currBead != NULL) {
                    cout << currBead->id << " ";

                    Bead* currLink = currBead->nextLink;

                    if(currLink != NULL) {
                        cout << currLink->ropeID1 << currLink->ropeID2 << currLink->ropeID3 << " " << currLink->id << " ";

                        while(currLink->hasNextLink()) {
                            Bead* nextLink = currLink->nextLink;

                            cout << nextLink->ropeID1 << nextLink->ropeID2 << nextLink->ropeID3 << " " << nextLink->id << " ";

                            currLink = currLink->nextLink;
                        }
                    }

                    cout << endl;

                    while(currBead->hasNext()) {
                        Bead* nextBead = currBead->nextBead;

                        cout << nextBead->id << " ";

                        currLink = nextBead->nextLink;

                        if(currLink != NULL) {
                            cout << currLink->ropeID1 << currLink->ropeID2 << currLink->ropeID3 << " " << currLink->id << " ";

                            while(currLink->hasNextLink()) {
                                Bead* nextLink = currLink->nextLink;

                                cout << nextLink->ropeID1 << nextLink->ropeID2 << nextLink->ropeID3 << " " << nextLink->id << " ";

                                currLink = currLink->nextLink;
                            }
                        }

                        currBead = currBead->nextBead;
                        cout << endl;
                    }
                }

                currRope = currRope->nextRope;
            }
        }
    }
};

static Construction* construction = new Construction();

void addNewRope(char id1, char id2, char id3) {

    Rope* newRope = new Rope(id1, id2, id3);

    construction->addRope(newRope);
}

void addNewBead(int beadID, char ropeID1, char ropeID2, char ropeID3) {

    Rope* rope = construction->getRope(ropeID1, ropeID2, ropeID3);

    if(rope != NULL) {
        Bead* newBead = new Bead(beadID, ropeID1, ropeID2, ropeID3);
        rope->addNewBead(newBead);
    }
}

void addNewLink(int beadFromID, char ropeFromID1, char ropeFromID2, char ropeFromID3,
                int beadID, char ropeID1, char ropeID2, char ropeID3) {

    Rope* ropeFrom = construction->getRope(ropeFromID1, ropeFromID2, ropeFromID3);
    Rope* ropeTo = construction->getRope(ropeID1, ropeID2, ropeID3);

    if(ropeFrom != NULL && ropeTo != NULL) {
        Bead* beadFrom = ropeFrom->getBead(beadFromID);
        Bead* beadTo = ropeTo->getBead(beadID);

        if(beadFrom != NULL && beadTo != NULL) {
            beadFrom->addNewLink(beadTo);
        }
    }
}

void deleteLink(int beadFromID, char ropeFromID1, char ropeFromID2, char ropeFromID3, int beadID, char ropeID1, char ropeID2, char ropeID3) {

    Rope* ropeFrom = construction->getRope(ropeFromID1, ropeFromID2, ropeFromID3);
    Rope* ropeTo = construction->getRope(ropeID1, ropeID2, ropeID3);

    if(ropeFrom != NULL && ropeTo != NULL) {
        Bead* beadFrom = ropeFrom->getBead(beadFromID);
        Bead* beadTo = ropeTo->getBead(beadID);

        if(beadFrom != NULL && beadTo != NULL) {
            beadFrom->deleteLink(beadTo);
        }

    }
}

void deleteBead(int beadID, char ropeID1, char ropeID2, char ropeID3) {

    Rope* rope = construction->getRope(ropeID1, ropeID2, ropeID3);

    if(rope != NULL) {
        Bead* bead = rope->getBead(beadID);
        if(bead != NULL) {
            construction->deleteAllLinksToBead(bead);
            rope->deleteBead(bead);
        }
    }
}

void relocateBead(int beadID, char ropeFromID1, char ropeFromID2, char ropeFromID3, char ropeID1, char ropeID2, char ropeID3) {

    Rope* ropeFrom = construction->getRope(ropeFromID1, ropeFromID2, ropeFromID3);
    Rope* ropeTo = construction->getRope(ropeID1, ropeID2, ropeID3);

    if(ropeFrom != NULL && ropeTo != NULL) {
        Bead* bead = ropeFrom->getBead(beadID);

        if(bead != NULL) {
            construction->relocateBead(bead, ropeFrom, ropeTo);
        }
    }

}

void deleteRope(char ropeID1, char ropeID2, char ropeID3) {

    Rope* ropeToDelete = construction->getRope(ropeID1, ropeID2, ropeID3);

    if(ropeToDelete != NULL) {

        while(ropeToDelete->firstBead != NULL) {

            Bead* currBead = ropeToDelete->firstBead;
            Bead* nextBead = currBead->nextBead;

            deleteBead(currBead->id, ropeID1, ropeID2, ropeID3);

            ropeToDelete->firstBead = nextBead;
        }

        construction->deleteRope(ropeToDelete);
    }
}

void displayAll() {

    construction->displayAll();

}

void deleteAllRopes() {

    while(construction->firstRope != NULL) {

        Rope* currRope = construction->firstRope;

        Rope* nextRope = currRope->nextRope;

        deleteRope(currRope->id1, currRope->id2, currRope->id3);

        construction->firstRope = nextRope;
    }

}

int main() {

    char operationChar;
    char ropeID1 = 0;
    char ropeID2 = 0;
    char ropeID3 = 0;
    char ropeFromID1;
    char ropeFromID2;
    char ropeFromID3;
    int beadID;
    int beadFromID;

    while(true) {

        cin >> operationChar;

        if(operationChar == 'S') {
            cin >> ropeID1 >> ropeID2 >> ropeID3;
            addNewRope(ropeID1, ropeID2, ropeID3);
        }
        else if(operationChar == 'B'){
            cin >> beadID >> ropeID1 >> ropeID2 >> ropeID3;
            addNewBead(beadID, ropeID1, ropeID2, ropeID3);
        }
        else if(operationChar == 'L') {
            cin >> beadFromID >> ropeFromID1 >> ropeFromID2 >> ropeFromID3 >> beadID >> ropeID1 >> ropeID2 >> ropeID3;
            addNewLink(beadFromID, ropeFromID1, ropeFromID2, ropeFromID3, beadID, ropeID1, ropeID2, ropeID3);
        }
        else if(operationChar == 'U') {
            cin >> beadFromID >> ropeFromID1 >> ropeFromID2 >> ropeFromID3 >> beadID >> ropeID1 >> ropeID2 >> ropeID3;
            deleteLink(beadFromID, ropeFromID1, ropeFromID2, ropeFromID3, beadID, ropeID1, ropeID2, ropeID3);
        }
        else if(operationChar == 'D') {
            cin >> beadID >> ropeID1 >> ropeID2 >> ropeID3;
            deleteBead(beadID, ropeID1, ropeID2, ropeID3);
        }
        else if(operationChar == 'M') {
            cin >> beadID >> ropeFromID1 >> ropeFromID2 >> ropeFromID3 >> ropeID1 >> ropeID2 >> ropeID3;
            relocateBead(beadID, ropeFromID1, ropeFromID2, ropeFromID3, ropeID1, ropeID2, ropeID3);
        }
        else if(operationChar == 'R') {
            cin >> ropeID1 >> ropeID2 >> ropeID3;
            deleteRope(ropeID1, ropeID2, ropeID3);
        }
        else if(operationChar == 'P') {
            displayAll();
        }
        else if(operationChar == 'F') {

            deleteAllRopes();
            delete(construction);
            break;
        }
    }

    return 0;
}
