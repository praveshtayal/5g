#include <iostream>
#include <vector>
#include <algorithm>
#include "rrc.h"
using namespace std;

static const int sequence_length = 127;

// return true if value between low and high
bool valid(const int val, const int low, const int high)
{
    return low <= val && val <= high;
}

// return pss (BPSK M-sequenec of length 127) based on N2
vector<int> pss_sequence(const int N2)
{
    vector<int> x{0, 1, 1, 0, 1, 1, 1};
    for(auto i=0; i+7<sequence_length; i++)
        x.push_back((x[i+4]+x[i])%2);

    vector<int> pss(sequence_length);
    for(auto n=0; n<sequence_length; n++)
    {
        int m = (n+(43*N2))%sequence_length;
        pss[n] = 1 - 2*x[m];
    }

    return pss;
}

// return sss (Gold sequenec of length 127) based on N1, N2
vector<int> sss_sequence(const int N1, const int N2)
{
    const int m0 = 15*(N1/112) + (5*N2); //9 cyclic shifts
    const int m1 = N1%112; // 112 cyclic shifts

    vector<int> x0(sequence_length), x1(sequence_length);
    x0[0] = x1[0] = 1;
    for(auto i=0; i+7<sequence_length; i++)
    {
        x0[i+7] = (x0[i+4]+x0[i])%2;
        x1[i+7] = (x1[i+1]+x1[i])%2;
    }

    vector<int> sss(sequence_length);
    for(auto n=0; n<sequence_length; n++)
    {
        sss[n] = (1 - 2*x0[(n+m0)%sequence_length]) * (1 - 2*x1[(n+m1)%sequence_length]);
    }

    return sss;
}

int choice()
{
    int input=0;
    while(!valid(input, 1, 2))
    {
        cout << "1: Generate PSS and SSS sequence from PCI.\n";
        cout << "2: Schedule SI Messages.\n";
        cout << "Please enter the choice: ";
        cin >> input;
    }

    return input;
}

void get_N1_N2(int &N1, int &N2)
{
    N1 = -1;
    do{
        cout << "N1(0-335): ";
        cin >> N1;
    }while(!valid(N1, 0, 335));

    N2 = -1;
    do{
        cout << "N2(0-2): ";
        cin >> N2;
    }while(!valid(N2, 0, 2));
}

void schedule_si(rrc_sl windowLength, vector<rrc_rf> siPeriodicity)
{

}

// To execute C++, please define "int main()"
int main() {
    int input = choice();

    switch(input)
    {
        case 1:
            {
                int N1, N2;
                get_N1_N2(N1, N2);

                int pci = (3*N1)+N2;
                cout << "PCI(0-1007) is " << pci << endl;

                vector<int> pss = pss_sequence(N2);
                cout << "PSS is BPSK M-sequenec of length 127 based on N2" << endl;
                for(auto i=0; i<sequence_length; i++)
                    cout << i << ':' << pss[i] << ' ';
                cout << endl;

                vector<int> sss = sss_sequence(N1, N2);
                cout << "SSS is Gold sequenec of length 127 based on N1, N2" << endl;
                for(auto i=0; i<sequence_length; i++)
                    cout << i << ':' << sss[i] << ' ';
                cout << endl;
                break;
            }
        case 2:
            {
                int x;
                cout << "windowLength(0-9): ";
                cin >> x;
                rrc_sl windowLength = static_cast<rrc_sl>(x);

                int siCount;
                cout << "siCount: ";
                cin >> siCount;

                vector<rrc_rf> siPeriodicity;
                for(auto i=0; i<siCount; i++)
                {
                    cout << "siPeriodicity(0-6) for SI Msg " << i << ": ";
                    cin >> x;
                    rrc_rf periodicity = static_cast<rrc_rf>(x);
                    siPeriodicity.push_back(periodicity);
                }
                schedule_si(windowLength, siPeriodicity);
                break;
            }

            return 0;
    }
}
