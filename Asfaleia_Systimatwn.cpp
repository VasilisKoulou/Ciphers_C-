#include <iostream>
#include <string>
#include <vector>

using namespace std;

void TranspositionCipher() {
    system("cls");
    string message;
    int t;
    vector<int> key;

    string plaintext;
    string ciphertext;
    string apokr;

    cout << "Dwse mou to block: ";
    cin >> t;

    key.resize(t);
    for (int i = 0; i < t; ++i) {
        cout << "Dwse mou kleidi gia tin thesi " << (i + 1) << ": ";
        cin >> key[i];
        if (key[i] > t) {
            return;
        }
        for (int j = 0; j < i; j++) {
            if (key[i] == key[j]) {
                return;
            }
        }
    }
    cin.ignore();

    cout << "Message: ";
    getline(cin, message);

    for (char c : message) {
        if ((c < 'A' || c > 'Z') && c != ' ') {
            return;
        }
        if (c != ' ') {
            plaintext += c;
        }
    }
    while (plaintext.size() % t != 0) {
        plaintext += 'X';
    }

    for (int i = 0; i < plaintext.size(); i += t) {
        string block;
        for (int j = 0; j < t; j++) {
            block.push_back(plaintext[i + j]);
        }
        for (int k = 0; k < t; k++) {
            ciphertext += block[key[k] - 1];
        }
        if (i + t < plaintext.size()) {
            ciphertext.push_back(' ');
        }
    }
    cout << "Encrypted Message: " << ciphertext << endl;

    vector<int> ant(t);
    for (int i = 0; i < t; i++) {
        ant[key[i] - 1] = i;
    }

    for (int i = 0; i < ciphertext.size(); i += (t + 1)) {
        string block;
        for (int j = 0; j < t; j++) {
            block.push_back(ciphertext[i + j]);
        }
        for (int k = 0; k < t; k++) {
            apokr += block[ant[k]];
        }
    }
    while (!apokr.empty() && apokr.back() == 'X') {
        apokr.pop_back();
    }
    cout << "Decrypted Message: " << apokr << endl;
}

void PolyalphabeticCipher() {
    system("cls");
    string message;
    vector<int> key;
    int t;

    string plaintext = "";
    string ciphertext = "";
    string kr = "";
    string apokr = "";

    cout << "Vale arithmo block: ";
    cin >> t;

    key.resize(t);
    for (int i = 0; i < t; ++i) {
        cout << "Vale to kleidi stin thesi " << (i + 1) << ": ";
        cin >> key[i];
    }
    cin.ignore();

    cout << "Message: ";
    getline(cin, message);

    for (char c : message) {
        if ((c < 'A' || c > 'Z') && c != ' ') {
            return;
        }
        if (c != ' ') {
            plaintext += c;
        }
    }

    while (plaintext.size() % t != 0) {
        plaintext += 'X';
    }

    for (int i = 0; i < plaintext.size(); i++) {
        char pC = plaintext[i];
        int met = key[i % key.size()] % 26;
        char eC = (pC - 'A' + met) % 26 + 'A';
        ciphertext += eC;

        if ((i + 1) % t == 0 && (i + 1) != plaintext.size()) {
            ciphertext += ' ';
        }
    }

    cout << "Encrypted Message: " << ciphertext << endl;

    for (char c : ciphertext) {
        if (c != ' ') {
            kr += c;
        }
    }

    for (int i = 0; i < kr.size(); i++) {
        char c = kr[i];
        int met = key[i % key.size()] % 26;
        char dC = (c - 'A' - met + 26) % 26 + 'A';
        apokr += dC;
    }

    while (!apokr.empty() && apokr.back() == 'X') {
        apokr.pop_back();
    }
    cout << "Decrypted Message: " << apokr << endl;
}

void StreamCipher() {
    system("cls");
    const int b = 5;
    string message, bin_key, key, bin_message, ciphertext, en_message, dbmessage, dec_message, deci_message;

    for (char c = 'A'; c <= 'Z'; c++) {
        int value = c - 'A' + 1;
        string bin = "";

        for (int i = b - 1; i >= 0; i--) {
            bin += '0' + ((value >> i) & 1);
        }

        cout << c << " -> " << bin << endl;
    }

    cout << "Binary Key: ";
    cin >> bin_key;

    if (bin_key.length() != b) {
        return;
    }

    for (int i = 0; i < bin_key.length(); i++) {
        if (bin_key[i] != '0' && bin_key[i] != '1') {
            return;
        }
    }
    cin.ignore();

    cout << "Message: ";
    getline(cin, message);

    for (char c : message) {
        if (c < 'A' || c > 'Z') {
            return;
        }
        int value = c - 'A' + 1;
        string bin = "";

        for (int j = b - 1; j >= 0; j--) {
            bin += '0' + ((value >> j) & 1);
        }

        bin_message += bin;
    }
    cout << "Binary Message:" << endl;
    for (int i = 0; i < bin_message.length(); i += b) {
        for (int j = 0; j < b; j++) {
            cout << bin_message[i + j];
        }
        cout << " ";
    }
    cout << endl;

    for (int i = 0; i < bin_message.length(); i += b) {
        string block = "";
        for (int j = 0; j < b; j++) {
            block += bin_message[i + j];
        }

        string ciblock = "";
        for (int j = 0; j < b; j++) {
            ciblock += (block[j] == bin_key[j]) ? '0' : '1';
        }
        ciphertext += ciblock;
    }

    cout << "Transposition Key: ";
    getline(cin, key);

    if (key.length() != b) {
        return;
    }

    for (int i = 0; i < ciphertext.length(); i += b) {
        string block = "";
        for (int j = 0; j < b; j++) {
            block += ciphertext[i + j];
        }

        string enblock = "     ";
        for (int j = 0; j < b; j++) {
            int position = key[j] - '1';
            enblock[position] = block[j];
        }
        en_message += enblock;
    }

    cout << "Encrypted Message:" << endl;
    for (int i = 0; i < en_message.length(); i += b) {
        for (int j = 0; j < b; j++) {
            cout << en_message[i + j];
        }
        cout << " ";
    }
    cout << endl;

    for (int i = 0; i < en_message.length(); i += b) {
        string block = "";
        for (int j = 0; j < b; j++) {
            block += en_message[i + j];
        }

        string dblock = "     ";
        for (int j = 0; j < b; j++) {
            int position = key[j] - '1';
            dblock[j] = block[position];
        }
        deci_message += dblock;
    }

    for (int i = 0; i < deci_message.length(); i += b) {
        string block = "";
        for (int j = 0; j < b; j++) {
            block += deci_message[i + j];
        }

        string dblock = "";
        for (int j = 0; j < b; j++) {
            dblock += (block[j] == bin_key[j]) ? '0' : '1';
        }
        dbmessage += dblock;
    }

    for (int i = 0; i < dbmessage.length(); i += b) {
        int value = 0;
        for (int j = 0; j < b; j++) {
            value = (value << 1) + (dbmessage[i + j] - '0');
        }
        dec_message += (value - 1) + 'A';
    }
    cout << "Decrypted Message: " << dec_message << endl;
}

int main() {
    int choice = 0;

    while (choice != 4) {
        cout << "Menu:" << endl;
        cout << "1) Substitution Cipher" << endl;
        cout << "2) Transposition Cipher" << endl;
        cout << "3) Stream Cipher" << endl;
        cout << "Dwse tin epilogi sou: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Epelekses Substitution Cipher\n";
            PolyalphabeticCipher();
            break;
        case 2:
            cout << "Epelekses Transposition Cipher\n";
            TranspositionCipher();
            break;
        case 3:
            cout << "Epelekses Stream Cipher\n";
            StreamCipher();
            break;
        }
    }

    return 0;
}
