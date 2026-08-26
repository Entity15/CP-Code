string s; cin >> s;
    vector<int> c;
    for(int i = 0; i < s.length(); i+2){
        c.push_back(int(s[i]));
    }
    sort(c.begin(),c.end());
    for(auto x : c){
        if(x == c.size()) cout << x;
        cout << x << "+";