#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#define pi 3.14
using namespace std;
struct analog
{
    int duration;
    int freq;
    int max;
    int min;
};
class signal
{
    vector<int> input;
    vector<int> output;
    analog b;
    vector<int> data;

public:
    int getdata();
    void getanalog();
    void NRZ_L();
    void NRZ_I();
    void manchester();
    void diff_manchester();
    void ami();
    void B82S();
    void HDB3();
    void pcm();
    void dm();
    void display();
} sg;
void signal::display()
{
    int a = output.size();
    for (int i = 0; i < a; i++)
    {
        cout << output[i];
    }
}
int signal::getdata()
{
    int n;
    cout << "\nEnter the number of bits:" << endl;
    cin >> n;
    int a;
    cout << "\nEnter the bits (press enter any entering each bit, i.e. enter one by one):";
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        input.push_back(a);
    }
    cout << "Choose the line encoding technique:\n1. NRZ-L 2. NRZ-I \n3. Manchester \n 4. Differential Manchester \n 5. AMI";
    int b;
    cin >> b;
    if (b == 1)
    {
        NRZ_L();
    }
    else if (b == 2)
    {
        NRZ_I();
    }
    else if (b == 3)
    {
        manchester();
    }
    else if (b == 4)
    {
        diff_manchester();
    }
    else
    {
        ami();
    }
    return n;
}
void signal::NRZ_L()
{
    int n = input.size();
    for (int i = 0; i < n; i++)
    {
        int a = input[i];
        if (a == 1)
        {
            output.push_back(1);
        }
        else
        {
            output.push_back(-1);
        }
    }
}
void signal::NRZ_I()
{
    int n = input.size();
    int a = input[0];
    if (a == 1)
    {
        output.push_back(1);
    }
    else
    {
        output.push_back(-1);
    }
    for (int i = 1; i < n; i++)
    {
        int a = input[i];
        if (a == 1)
        {
            if (output[i - 1] == 1)
            {
                output.push_back(-1);
            }
            else
            {
                output.push_back(1);
            }
        }
        else
        {
            int j = output[i - 1];
            output.push_back(j);
        }
    }
}
void signal::manchester()
{
    int n = input.size();
    for (int i = 0; i < n; i++)
    {
        int a = input[i];
        if (a == 0)
        {
            output.push_back(1);
            output.push_back(-1);
        }
        else
        {
            output.push_back(-1);
            output.push_back(1);
        }
    }
}
void signal::diff_manchester()
{
    int n = input.size();
    int k = input[0];
    int x = -1;
    if (k == 0)
    {
        output.push_back(-1);
        x++;
        output.push_back(1);
        x++;
    }
    else
    {
        output.push_back(1);
        x++;
        output.push_back(-1);
        x++;
    }
    for (int i = 1; i < n; i++)
    {
        int a = input[i];
        if (a == 0)
        {
            int j = output[x];
            if (j == 1)
            {
                output.push_back(-1);
                x++;
                output.push_back(1);
                x++;
            }
            else
            {
                output.push_back(1);
                x++;
                output.push_back(-1);
                x++;
            }
        }
        else
        {
            int j = output[x];
            output.push_back(j);
            x++;
            if (j == 1)
            {
                output.push_back(-1);
                x++;
            }
            else
            {
                output.push_back(1);
                x++;
            }
        }
    }
}
void signal::ami()
{
    int a;
    cout << "Enter whether you want scrambled or not:\n1. yes \n0. no)";
    cin >> a;
    if (a == 0)
    {
        int transitions = 0;
        int n = input.size();
        for (int i = 0; i < n; i++)
        {
            int x = input[i];
            if (x == 0)
            {
                output.push_back(0);
            }
            else
            {
                if (transitions == 0)
                {
                    output.push_back(1);
                    transitions = 1;
                }
                else
                {
                    output.push_back(-1);
                    transitions = 0;
                }
            }
        }
    }
    else
    {
        int y;
        cout << "Enter the type of scrambling:\n0. B82S \n1. HDB3 )";
        cin >> y;
        if (y == 0)
        {
            B82S();
        }
        else
        {
            HDB3();
        }
    }
}
void signal::B82S()
{
    int transitions = 0;
    int count = 0;
    int n = input.size();
    for (int i = 0; i < n; i++)
    {
        int x = input[i];
        if (count == 8)
        {
            output[i - 8] = 0;
            output[i - 7] = 0;
            output[i - 6] = 0;
            output[i - 3] = 0;
            int z = output[i - 9];
            if (z == -1)
            {
                output[i - 5] = -1;
                output[i - 4] = 1;
                output[i - 2] = 1;
                output[i - 1] = -1;
                transitions = 0;
            }
            else
            {
                output[i - 5] = 1;
                output[i - 4] = -1;
                output[i - 2] = -1;
                output[i - 1] = 1;
                transitions = 1;
            }
            count = 0;
        }
        if (x == 0)
        {
            output.push_back(0);
            count++;
        }
        else
        {
            count=0;
            if (transitions == 0)
            {
                output.push_back(1);
                transitions = 1;
            }
            else
            {
                output.push_back(-1);
                transitions = 0;
            }
        }
    }
}
void signal::HDB3()
{
    int transitions = 0;
    int count_nz = 0;
    int count = 0;
    int n = input.size();
    for (int i = 0; i < n; i++)
    {
        int x = input[i];
       
        if (x == 0)
        {
            output.push_back(0);
            count++;
        }
        else
        {
            count=0;
            count_nz++;
            if (transitions == 0)
            {
                output.push_back(1);
                transitions = 1;
            }
            else
            {
                output.push_back(-1);
                transitions = 0;
            }
        }
     if (count == 4)
        {
            if (count_nz % 2 == 0)
            {

                int f = output[i - 4];
                if (f == 1)
                {
                    output[i - 3] = -1;
                    output[i - 2] = 0;
                    output[i - 1] = 0;
                    output[i] = -1;
                    transitions = 0;
                }
                else
                {
                    output[i - 3] = 1;
                    output[i - 2] = 0;
                    output[i - 1] = 0;
                    output[i] = 1;
                    transitions = 1;
                }
                count_nz = 0;
            }
            else
            {
                output[i - 4] = 0;
                output[i - 3] = 0;
                output[i - 2] = 0;
                int r = output[i - 5];
                if (r == 1)
                {
                    output[i - 1] = 1;
                    transitions = 1;
                }
                else
                {
                    output[i - 1] = -1;
                    transitions = 0;
                }
                count_nz = 0;
            }
            count = 0;
        }
    }
}
void signal::getanalog()
{
    cout << "Enter the duration of signal,frequency of signal,max amplitude and minimum amplitude(for the sine signal):";
    cin >> b.duration >> b.freq >> b.max >> b.min;
    pcm();
}
void signal::pcm()
{
    const int levels = 256;
    int n_freq = 4 * b.freq;
    int n = n_freq * b.duration;
    float time_period = 1.0 / b.freq;
    float s = 1.0 / n_freq;
    vector<float> samples;
    for (int i = 0; i < n; i++)
    {
        double c = (i + 1) * s * ((2 * pi) / time_period);
        float a = b.max * sin(c);
        samples.push_back(a);
    }
    float step_size = (float)(b.max - b.min) / levels;
    vector<float> quantization_values;
    float z = b.min + step_size / 2;
    quantization_values.push_back(z);
    for (int i = 1; i < levels; i++)
    {
        float temp = quantization_values[i - 1] + step_size;
        quantization_values.push_back(temp);
    }

    map<float, vector<int>> mp;
    int y = quantization_values.size();
    vector<int> bits(8, 0);
    int k = 0;
    for (int i = 0; i < y; i++)
    {
        int n = k, j = 7;
        while (n != 0)
        {
            bits[j] = n % 2;
            j--;
            n = n / 2;
        }
        mp[quantization_values[i]] = bits;
        k++;
        for (int m = 0; m < 8; m++)
        {
            bits[m] = 0;
        }
    }

    int d = samples.size();
    for (int i = 0; i < d; i++)
    {
        float h = samples[i];
        int j;
        for (j = 0; j < (levels - 1); j++)
        {
            if (h <= quantization_values[j + 1] && h >= quantization_values[j])
            {
                samples[i] = quantization_values[j];
                break;
            }
        }
        if (j == (levels - 1))
        {
            samples[i] = quantization_values[j];
        }
    }
    vector<int> temp(8, 0);
    int w = samples.size();
    for (int f = 0; f < w; f++)
    {
        temp = mp[samples[f]];
        for (int g = 0; g < 8; g++)
        {
            int o = temp[g];
            data.push_back(o);
        }
    }
    cout << "Do you want to view data or call a line encoding:\n0. Data \n1. line encoding)";
    int a;
    cin >> a;
    if (a == 0)
    {
        int size = data.size();
        for (int i = 0; i < size; i++)
        {
            cout << data[i];
        }
    }
    else
    {
        int size = data.size();
        for (int i = 0; i < size; i++)
        {
            int tem=data[i];
            input.push_back(tem);
        }
        cout << "Choose the line encoding technique:\n1. NRZ-L 2. NRZ-I \n3. Manchester \n 4. Differential Manchester \n 5. AMI";
        int b;
        cin >> b;
        if (b == 1)
        {
            NRZ_L();
        }
        else if (b == 2)
        {
            NRZ_I();
        }
        else if (b == 3)
        {
            manchester();
        }
        else if (b == 4)
        {
            diff_manchester();
        }
        else
        {
            ami();
        }
    }
}
int main()
{
    cout << "Enter whether the data is analog or digital(0 or 1):\n0. analog \n1. digital:\n ";
    int a;
    cin >> a;
    if (a == 0)
    {
        sg.getanalog();
    }
    else
    {
        sg.getdata();
    }
    sg.display();
    return 0;
}