#include<bits/stdc++.h>
#include<chrono>
#include<thread>
#include"Trie.h"
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

const string dictionary="dictionary.txt";
unsigned int microsecond = 1000000;

class Boggle;
static void searchWord(int i,int j,string,Boggle*,Trie*);
class Boggle {
    public:
        int row;
        int col;
        vector<string>mat;
        vector<vector<bool>>visited;
        set<string>solutions;
        Boggle(int n,int m) {
            this->row=n;
            this->col=n;
            this->mat.resize(n);
            this->visited=vector<vector<bool>>(n,vector<bool>(m));
            cout<<"Enter board values of "<<n<<" by "<<m<<endl;
            vector<string>a{"hello","onder","telad","hoatr"};
            for(int i=0;i<n;i++)
                cin>>this->mat[i];
        }
        void findSolution(Trie *root) {
            for(int i=0;i<this->row;i++)
            {
                for(int j=0;j<this->col;j++)
                    searchWord(i,j,"",this,root);
            }
        }
        void printSolution(Trie* root){
            cout<<"Finding Solutions";
            for(int i=0;i<50;i++)
            {
                cout<<"."<<flush;
                sleep_for(microseconds(rand()%200000+1));
            }
            cout<<endl;
            if(solutions.size()==0)
                findSolution(root);
            for(auto i:solutions)
                cout<<i<<endl;
            if(solutions.size()==0)
                cout<<"No words are found in Boggle"<<endl;
            else cout<<"Total "<<solutions.size()<<((solutions.size()==1)?(" word"):(" words"))<<" found"<<endl;
        }
};
void searchWord(int i,int j,string s,Boggle* boggle,Trie* root) {
    char x=boggle->mat[i][j];
    if(root->child[x-'a']==NULL)
        return;
    s+=x;
    boggle->visited[i][j]=true;
    if(root->child[x-'a']->isLeaf)
        boggle->solutions.insert(s);
    if(j+1<boggle->col && !(boggle->visited[i][j+1]))
        searchWord(i,j+1,s,boggle,root->child[x-'a']);
    if(i+1<boggle->row && !boggle->visited[i+1][j])
        searchWord(i+1,j,s,boggle,root->child[x-'a']);
    if(j-1>=0 && !boggle->visited[i][j-1])
        searchWord(i,j-1,s,boggle,root->child[x-'a']);
    if(i-1>=0 && !boggle->visited[i-1][j])
        searchWord(i-1,j,s,boggle,root->child[x-'a']);
    s.pop_back();
    boggle->visited[i][j]=false;
}
int main() {
    Trie* root=new Trie(dictionary);
    cout<<"Enter desired number of rows and cols"<<endl;
    int n,m;
    cin>>n>>m;
    Boggle board(n,m);
    board.printSolution(root);
}
