#include <bits/stdc++.h>
#include <regex>
#define all(v) begin(v), end(v)
using namespace std;
int main()
{
    freopen("backup.sql", "r", stdin);

    string pattern = R"((CREATE TABLE \w+\.(\w+)\s\()|(\s+(\w+)\s(\w+).+,?\n)|(\);))";
    regex r(pattern);
    string sql = "";
    while(!cin.eof())
    {
        string tmp;
        getline(cin, tmp);
        if(tmp.find("CREATE TABLE") != string::npos)
        {
            sql = "";
        }
        sql += tmp;
        sql += "\n";
        if(tmp == ");")
        {
            string result = regex_replace(sql, r, "$4,$5\n");
            sregex_iterator it(all(sql), r);
            string namefile = (*it).str(2) + ".csv";
            freopen(namefile.c_str(), "w", stdout);
            cout << "Attribute,Datatype,Description" << endl;
            stringstream ss(result);
            while(!ss.eof())
            {
                string s;
                ss >> s;
                if(s.size() && s[0] != ',' && s.find("CONSTRAINT") == string::npos) cout << s << ',' << endl;
            }
        }
    }

    return 0;
}