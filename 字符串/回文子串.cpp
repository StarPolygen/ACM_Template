



//ͳ�ƻ����Ӵ��� �������㷨 
ll countSubstrings(string s) {
 //Ԥ����
	string t = "#";
 	for (int i = 0; i < s.size(); ++i) {
 		t += s[i];
 		t += "#";
 	}
 	vector<ll> RL(t.size(), 0);
 	ll MaxRight = 0, pos = 0;
 	ll res = 0;
 	for (int i = 0; i < t.size(); ++i) {
 		RL[i] = MaxRight > i ? min(RL[2 * pos - i], MaxRight - i): 1;
		while (i-RL[i] >=0 && i+RL[i] < t.size() && t[i + RL[i]] == t[i - RL[i]])//��չ��ע��߽�
	 		++RL[i];
	 	//�������Ҷ˼�������
	 	if (MaxRight < i + RL[i] -1) {
	 		MaxRight = i + RL[i] -1;
	 		pos = i;
	 	}
	 	res += RL[i]/2;
 	}
 	return res;
}
