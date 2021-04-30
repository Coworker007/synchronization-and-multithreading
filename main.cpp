#include<bits/stdc++.h>
using namespace std;

int largestFiboLessOrEqual(int n,int fib[])
{
    fib[0] = 1;  // Fib[0] stores 2nd Fibonacci No.
    fib[1] = 2;  // Fib[1] stores 3rd Fibonacci No.

    // Keep Generating remaining numbers while previously
    // generated number is smaller
    int i;
    for (i=2; fib[i-1]<=n; i++)
        fib[i] = fib[i-1] + fib[i-2];

    // Return index of the largest fibonacci number
    // smaller than or equal to n. Note that the above
    // loop stopped when fib[i-1] became larger.
    return (i-2);

}//largestFiboLessOrEqual

string fibonacciEncoding(int n)
{
  int fib[30];
  int index = largestFiboLessOrEqual(n,fib);
  int i=index;
  char codeword[index+3];
  while (n)
    {
        // Mark usage of Fibonacci f (1 bit)
        codeword[i] = '1';

        // Subtract f from n
        n = n - fib[i];

        // Move to Fibonacci just smaller than f
        i = i - 1;

        // Mark all Fibonacci > n as not used (0 bit),
        // progress backwards
        while (i>=0 && fib[i]>n)
        {
            codeword[i] = '0';
            i = i - 1;
        }
    }
    codeword[index+1] = '1';
    string code="";
    for(i=0;i<=index+1;i++)
        code=code+codeword[i];
    return code;

}//fibonacciEncoding


/* driver function */
int main()
{
    int n,i,initial,j;
    ifstream inFile;
    inFile.open("STDIN4.txt");
    ofstream outFile;
    outFile.open("STDOUT4.txt");
    string str;
     string compile,cname;

    vector<pair<char, int> > v, store;
    int chk=0,count=0;

    while(!inFile.eof())     //reading STDIN Input text file
        {
        getline(inFile,str);
        if(chk==0){
            int value=0;
            for(j=0;j<str.length();j++){
                value=(value*10) + (str[j]-'0');
            }
            n=value; //n stores the total number of symbols
            chk++;
        }
        else{
            count++;
            if(count==n+1){
                cname=str; //cname stores compressed filename
                continue;
            }
            initial=2;
            if(str[1]!=' '){
                initial=0;
            }
            int value=0;
            for(j=initial;j<str.length();j++){
                value=(value*10) + (str[j]-'0');
            }
            if(str[1]!=' '){
                 v.push_back(make_pair(' ',value));
                 store.push_back(make_pair(' ',value));
             }
             else{
                 v.push_back(make_pair(str[0],value));
                 store.push_back(make_pair(str[0],value));
             }
            }

         }


    ifstream inFile1;
    inFile1.open(cname);
    inFile1>>compile;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(v[i].second>v[j].second){  //sorting the symbols on basis of frequency and ASCII value
                swap(v[i],v[j]);
            }
            else if(v[i].second==v[j].second){
                int fir=(int)(v[i].first);
                int sec=(int)(v[j].first);
                if(sec<fir){
                    swap(v[i],v[j]);
                }
            }
        }
    }

    map<char,int> m;
    string ans;
    for(i=0;i<n;i++){
        m[v[i].first]=i+1;
        for(j=0;j<v[i].second;j++){
            ans=ans+v[i].first;
        }
    }

    for(i=0;i<n;i++){
         outFile<<"Symbol: "<<store[i].first<<", Frequency: "<<store[i].second<<", Code: "<<fibonacciEncoding(m[store[i].first])<<endl;
    }

    sort(ans.begin(), ans.end());
    reverse(ans.begin(),ans.end());

    do {
        string check;
       for(i=0;i<ans.length();i++){
           int temp=m[ans[i]];
           check=check+fibonacciEncoding(temp);
       }
       if(check==compile){
           outFile<<"Decompressed message = "<<ans<<endl;
           break;
       }
    } while (prev_permutation(ans.begin(), ans.end()));

    return 0;

}//main
