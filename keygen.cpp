#include <iostream>
#include<algorithm>
#include <string>
#include <unordered_map>
#include<vector>

using namespace std;

// hexadecimal to binary conversion 
string hex2bin(string s) 
{ 
    
    unordered_map<char, string> mp; 
    mp['0'] = "0000"; 
    mp['1'] = "0001"; 
    mp['2'] = "0010"; 
    mp['3'] = "0011"; 
    mp['4'] = "0100"; 
    mp['5'] = "0101"; 
    mp['6'] = "0110"; 
    mp['7'] = "0111"; 
    mp['8'] = "1000"; 
    mp['9'] = "1001"; 
    mp['A'] = "1010"; 
    mp['B'] = "1011"; 
    mp['C'] = "1100"; 
    mp['D'] = "1101"; 
    mp['E'] = "1110"; 
    mp['F'] = "1111"; 
    string bin = ""; 
    for (int i = 0; i < s.size(); i++) { 
        bin += mp[s[i]]; 
    } 
    return bin; 
} 

// binary to hexadecimal conversion 
string bin2hex(string s) 
{ 
    
    unordered_map<string, string> mp; 
    mp["0000"] = "0"; 
    mp["0001"] = "1"; 
    mp["0010"] = "2"; 
    mp["0011"] = "3"; 
    mp["0100"] = "4"; 
    mp["0101"] = "5"; 
    mp["0110"] = "6"; 
    mp["0111"] = "7"; 
    mp["1000"] = "8"; 
    mp["1001"] = "9"; 
    mp["1010"] = "A"; 
    mp["1011"] = "B"; 
    mp["1100"] = "C"; 
    mp["1101"] = "D"; 
    mp["1110"] = "E"; 
    mp["1111"] = "F"; 
    string hex = ""; 
    for (int i = 0; i < s.length(); i += 4) { 
        string ch = ""; 
        ch += s[i]; 
        ch += s[i + 1]; 
        ch += s[i + 2]; 
        ch += s[i + 3]; 
        hex += mp[ch]; 
    } 
    return hex; 
} 




string permute(string k, int* arr, int n) 
{ 
    string per = ""; 
    for (int i = 0; i < n; i++) { 
        per += k[arr[i] - 1]; 
    } 
    return per; 
} 

string shift_left(string k, int shifts) 
{ 
    string s = ""; 
    for (int i = 0; i < shifts; i++) { 
        for (int j = 1; j < 28; j++) { 
            s += k[j]; 
        } 
        s += k[0]; 
        k = s; 
        s = ""; 
    } 
    return k; 
}


int main() {
  std::cout << "Hello World!\n";
  string key,left,right;
  std::cout<<"Enter 64 bit key(in hexadecimal): "; 
    cin>>key;

  /* *******************************************
  *********  ALL Table Used  ******************/  
  //Parity Bit Drop Table 
int keyp[56] = { 57, 49, 41, 33, 25, 17, 9, 
                     1, 58, 50, 42, 34, 26, 18, 
                     10, 2, 59, 51, 43, 35, 27, 
                     19, 11, 3, 60, 52, 44, 36, 
                     63, 55, 47, 39, 31, 23, 15, 
                     7, 62, 54, 46, 38, 30, 22, 
                     14, 6, 61, 53, 45, 37, 29, 
                     21, 13, 5, 28, 20, 12, 4 }; 


  int key_comp[48] = { 14, 17, 11, 24, 1, 5, 
                         3, 28, 15, 6, 21, 10, 
                         23, 19, 12, 4, 26, 8, 
                         16, 7, 27, 20, 13, 2, 
                         41, 52, 31, 37, 47, 55, 
                         30, 40, 51, 45, 33, 48, 
                         44, 49, 39, 56, 34, 53, 
                         46, 42, 50, 36, 29, 32 }; 

    int shift_table[16] = { 1, 1, 2, 2, 
                            2, 2, 2, 2, 
                            1, 2, 2, 2, 
                            2, 2, 2, 1 }; 

   /*******************************************
   ******************************************/                         
  //After removig parity Bit 
    key = permute(key, keyp, 56); 

    //Left and Right subkey
     left = key.substr(0, 28); 
     right = key.substr(28, 28); 
  
    vector<string> round_key_binary;
    vector<string> round_key_hexa; 


    for (int i = 0; i < 16; i++) { 
        // Shifting 
        left = shift_left(left, shift_table[i]); 
        right = shift_left(right, shift_table[i]); 
  
        // Combining 
        string combine = left + right; 
  
        // Key Compression 
        string RoundKey = permute(combine, key_comp, 48); 
        string temp=bin2hex(RoundKey);
      std::cout<<"\n Round "<<i+1<< " 48 bit Key in Binary is"<<RoundKey;
      std::cout<<"\n Round "<<i+1<< " 48 bit Key in HexaDecimal is"<<temp;
      std::cout<<"\n";
        round_key_binary.push_back(RoundKey); 
        round_key_hexa.push_back(bin2hex(RoundKey)); 
    } 
}
