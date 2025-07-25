// Syed muhammad zarrar jawad
// 35027
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct Node
{
    string word;
    int count;
    Node* next;
};

void Add_node(Node*& head, string word, int count) {
    Node* newNode = new Node;
    newNode->word = word;
    newNode->count = count;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int exists(Node* header, string word)
{
    int exist_count = 0;
    Node* temp = header;
    while (temp != nullptr) {
        if (temp->word == word) {
            exist_count++;
        }

        temp = temp->next;
    }
    return exist_count;
}

void remove(Node*& head, string word) {
    Node* temp = head;
    Node* prev = nullptr;

    while (temp != nullptr) {
        if (temp->word == word) {
            if (prev == nullptr) {
                head = temp->next;
                delete temp;
                temp = head;
            }
            else {
                prev->next = temp->next;
                delete temp;
                temp = prev->next;
            }
        }
        else {
            prev = temp;
            temp = temp->next;
        }
    }
}

void traverse(Node* head) {
    Node* temp = head;
    int counter = 0;
    while (temp != nullptr) {
        cout << temp->word <<"("<< temp->count<<") --> ";
        temp = temp->next;
        counter ++;
        if (counter % 5 == 0) {
            cout << endl;
        }
    }
}

void third_list(Node*& head3, string word, int count) {
    Node* temp = head3;
    while (temp != nullptr) {
        if (temp->word == word) {
            temp->count += count;
            return;
        }
        temp = temp->next;
    }
    Add_node(head3, word, count+1);
}
//buuble sort approach
void sort(Node*& head) {
    Node* temp1 = head;
    while (temp1 != nullptr) {
        Node* temp2 = head;

        while (temp2->next != nullptr) {
            if (temp2->count > temp2->next->count ||
               ((temp2->count == temp2->next->count) && temp2->word > temp2->next->word)) {
                string tempWord = temp2->word;
                int tempCount = temp2->count;

                temp2->word = temp2->next->word;
                temp2->count = temp2->next->count;

                temp2->next->word = tempWord;
                temp2->next->count = tempCount;
               }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
}
void deleteList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    ifstream input_file1;
    ifstream input_file2;
    string filename1, filename2, line1, line2, file1_word, file2_word;
    bool file1_flag = false;
    bool file2_flag = false;
// opening first file
    cout << "Please enter the first file name:" << endl;
    cin >> filename1;
    input_file1.open(filename1);
    while (!file1_flag) {
        if (!input_file1) {
            cout << "The file couldn't be opened."<<endl;
            cout << "Please enter a valid file name:"<<endl;
            cin >> filename1;
            input_file1.open(filename1);
        }
        else {
            file1_flag = true;
        }
    }
// opening second file

    cout << "Please enter the second file name:" << endl;
    cin >> filename2;
    input_file2.open(filename2);
    while (!file2_flag) {
        if (!input_file2) {
            cout << "The file couldn't be opened."<<endl;
            cout << "Please enter a valid file name:"<<endl;
            cin >> filename2;
            input_file2.open(filename2);
        }
        else {
            file2_flag = true;
        }
    }

    string word1, word2;
    bool ending_flag1 = true;
    bool ending_flag2 = true;
    bool file1_Words = true;
    bool file2_Words = true;
    Node *head1 = nullptr;
    Node *head2 = nullptr;
    Node *head3 = nullptr;
    while (file1_Words || file2_Words) {
        if (file1_Words && (input_file1 >> word1)) {
            cout <<"Processing the word "<<'"'<<word1<<'"'<<" from the 1st file."<<endl;

            int exists_first = exists(head1, word1);
            int exists_second = exists(head2, word1);
            int exists_third = exists(head3, word1);
            if (exists_second >= 1 || (exists_first+exists_second >= 2)||exists_third >=1) {
                remove(head1, word1);
                remove(head2, word1);
                third_list(head3, word1, exists_third + exists_first + exists_second);
            }
            else {
                remove(head1, word1);

                Add_node(head1, word1, exists_first+1);

            }
        }
        else {
            file1_Words = false;
            ending_flag1 = false;
        }

        if (file2_Words && (input_file2 >> word2)) {
            cout <<"Processing the word "<<'"'<<word2<<'"'<<" from the 2nd file."<<endl;
            int exists_first_s = exists(head1, word2);
            int exists_second_s = exists(head2, word2);
            int exists_third_s = exists(head3, word2);
            if (exists_first_s >= 1  || (exists_first_s+exists_second_s == 2)|| exists_third_s >= 1) {
                remove(head2, word2);
                remove(head1, word2);
                third_list(head3, word2, exists_third_s + exists_first_s + exists_second_s);

            }
            else {
                remove(head2, word2);
                Add_node(head2, word2, exists_second_s+1);

            }
        }
        else {
            file2_Words = false;
            ending_flag2 = false;
        }
        sort(head1);
        sort(head2);
        sort(head3);
        if (ending_flag1 || ending_flag2) {
            cout << endl;

            cout <<"List for File 1:"<<endl;
            traverse(head1);
            cout<<"--||";
            cout<<endl;
            cout<<endl;
            cout <<"List for File 2:"<<endl;
            traverse(head2);
            cout<<"--||";

            cout<<endl;
            cout<<endl;
            cout <<"Common List:"<<endl;
            traverse(head3);
            cout<<"--||";
            cout<<endl;
            cout<<endl;
            cout << "#############"<<endl;
            cout<<endl;
        }
    }
    cout<<"End of Files.";
    input_file1.close();
    input_file2.close();
    deleteList(head1);
    deleteList(head2);
    deleteList(head3);
    head1 = nullptr;
    head2 = nullptr;
    head3 = nullptr;
    cout <<"head1: " <<head1<<endl;
    cout << &head2;
    return 0;
}