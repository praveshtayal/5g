#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// return true if value between low and high
bool valid(const int val, const int low, const int high)
{
    return low <= val && val <= high;
}

// return pss (BPSK M-sequenec of length 127) based on N2
vector<int> pss_sequence(const int N2)
{
    vector<int> x{0, 1, 1, 0, 1, 1, 1};
    for(auto i=0; i+7<127; i++)
        x.push_back((x[i+4]+x[i])%2);

    vector<int> pss(128);
    for(auto n=0; n<128; n++)
    {
        int m = (n+(43*N2))%127;
        pss[n] = 1 - 2*x[m];
    }

    return pss;
}

// return sss (Gold sequenec of length 127) based on N1, N2
vector<int> sss_sequence(const int N1, const int N2)
{
    const int m0 = 15*(N1/112) + (5*N2); //9 cyclic shifts
    const int m1 = N1%112; // 112 cyclic shifts

    vector<int> x0(128), x1(128);
    x0[0] = x1[0] = 1;
    for(auto i=0; i+7<128; i++)
    {
        x0[i+7] = (x0[i+4]+x0[i])%2;
        x1[i+7] = (x1[i+1]+x1[i])%2;
    }

    vector<int> sss(128);
    for(auto n=0; n<128; n++)
    {
        sss[n] = (1 - 2*x0[(n+m0)%127]) * (1 - 2*x1[(n+m1)%127]);
    }

    return sss;
}


// To execute C++, please define "int main()"
int main() {

    int N1 = -1;
    do{
        cout << "N1(0-335): ";
        cin >> N1;
    }while(!valid(N1, 0, 335));

    int N2 = -1;
    do{
        cout << "N2(0-2): ";
        cin >> N2;
    }while(!valid(N2, 0, 2));

    int pci = (3*N1)+N2;
    cout << "PCI(0-1007) is " << pci << endl;

    vector<int> pss = pss_sequence(N2);
    cout << "PSS is BPSK M-sequenec of length 127 based on N2" << endl;
    for(auto i=0; i<128; i++)
        cout << i << ':' << pss[i] << ' ';
    cout << endl;

    vector<int> sss = sss_sequence(N1, N2);
    cout << "SSS is Gold sequenec of length 127 based on N1, N2" << endl;
    for(const auto i: sss)
        cout << i << ' ';
    cout << endl;

    return 0;
}
