#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

struct Company {
    string name;
    string profit_tax;
    string address;
};

struct HashTable {
    Company* table;      
    bool* occupied;      // Đánh dấu ô đã được dùng
    int size = 2000;
};

vector<Company> readCompanyList(string file_name) {
    vector<Company> cty;       
    ifstream file(file_name);      
    string line;

    if (!file) {
        cout << "Khong the mo file!!! "<< endl;
        return cty;            
    }

    getline(file, line); 
    while (getline(file, line)) {     
        stringstream ss(line);        
        Company c;
    
        if (getline(ss, c.name, '|') &&
            getline(ss, c.profit_tax, '|') &&
            getline(ss, c.address)) {
            cty.push_back(c);   
        }
    }
    file.close();
    return cty;                 
}

long long hashString(string company_name) {
	string s=company_name;
	if (s.length() > 20) {
		s = company_name.substr(company_name.length() - 20);
	}
	int p = 31, m = 2000;
	long long val = 0;
	long long pow = 1;
	for (int i = 0; i <s.length() ; i++) {
		val =( val + int(s[i]) * pow) % m;
		pow =(pow*p) % m;
	}
	return val;
}

HashTable* createHashTable(vector<Company> list_company) {
    HashTable* ht = new HashTable;
    ht->size = 2000;
    ht->table = new Company[ht->size];
    ht->occupied = new bool[ht->size];

    for (int i = 0; i < ht->size; ++i) {
        ht->occupied[i] = false;
    }

    for (int i = 0; i < (int)list_company.size(); ++i) {
        Company company = list_company[i];
        long long hash = hashString(company.name) % ht->size;

        while (ht->occupied[hash]) {
            hash = (hash + 1) % ht->size;
        }

        ht->table[hash] = company;
        ht->occupied[hash] = true;
    }
    return ht;
}

void insert(HashTable* hash_table, Company company) {
    long long idx = hashString(company.name) % hash_table->size;
    // linear probing
    while (hash_table->occupied[idx]) {
        idx = (idx + 1) % hash_table->size;
    }
    hash_table->table[idx] = company;
    hash_table->occupied[idx] = true;
}

Company* search(HashTable* hash_table, string company_name) {
    long long idx = hashString(company_name) % hash_table->size;
    int org_idx = idx;
    while (hash_table->occupied[idx]) {
        if (hash_table->table[idx].name == company_name) {
            return &(hash_table->table[idx]);
        }
        idx = (idx + 1) % hash_table->size;
        if (idx == org_idx) break;
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: ./main MST.txt input.txt output.txt\n";
        return 1;
    }

    string mst_file = argv[1];
    string input_file = argv[2];
    string output_file = argv[3];

    vector<Company> list_company = readCompanyList(mst_file);

    HashTable* ht = createHashTable(list_company);

    ifstream fin(input_file);
    ofstream fout(output_file);

    string line;
    while (getline(fin, line)) {
        Company* found = search(ht, line);
        if (found != NULL) {
            fout << found->name << "|" << found->profit_tax << "|" << found->address << endl;
        }
    }

    fin.close();
    fout.close();
    return 0;
}

