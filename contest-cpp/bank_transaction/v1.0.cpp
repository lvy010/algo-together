using namespace std;

class Bank {
    vector<long long> b;
    bool ok(int a){ return 1 <= a && a <= (int)b.size(); }
public:
    Bank(vector<long long>& balance): b(balance) {}
    bool transfer(int a, int c, long long m){
        if(!ok(a) || !ok(c) || b[a-1] < m) return false;
        b[a-1] -= m; b[c-1] += m; return true;
    }
    bool deposit(int a, long long m){
        if(!ok(a)) return false;
        b[a-1] += m; return true;
    }
    bool withdraw(int a, long long m){
        if(!ok(a) || b[a-1] < m) return false;
        b[a-1] -= m; return true;
    }
};