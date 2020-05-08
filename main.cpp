#include <iostream>
#include <string>

#define max_token 1000
using namespace std;

enum token_type {
	num, add, sub, mul, divide, left_brac, right_brac
};

struct token {
	token_type type;
	int value;
};

int m=0;

token tokens[1000];

int get_token(string s)
{
	int left = 0, right = 0;
	int state = 1;
	int len = s.length();
	int token_num = 0;
	while (right < len) {
		switch (state) {
			case 1:
				if (s[right] >= '0' && s[right] <= '9') {
					left = right;
					right++;
					state = 2;
				} else if (s[right] == '+') {
					left = right;
					right++;
					state = 3;
				} else if (s[right] == '-') {
					left = right;
					right++;
					state = 4;
				} else if (s[right] == '*') {
					left = right;
					right++;
					state = 5;
				} else if (s[right] == '/') {
					left = right;
					right++;
					state = 6;
				} else if (s[right] == '(') {
					left = right;
					right++;
					state = 7;
				} else if (s[right] == ')') {
					left = right;
					right++;
					state = 8;
				}
				break;
			case 2:
				if (s[right] >= '0' && s[right] <= '9') {
					right++;
					state = 2;
				} else {
					state = 1;
					tokens[token_num].type = num;
					tokens[token_num++].value = atoi(s.substr(left, right - left).c_str());
				}
				break;
			case 3:
				state = 1;
				tokens[token_num].type = add;
				tokens[token_num++].value = -1;
				break;
			case 4:
				state = 1;
				tokens[token_num].type = sub;
				tokens[token_num++].value = -1;
				break;
			case 5:
				state = 1;
				tokens[token_num].type = mul;
				tokens[token_num++].value = -1;
				break;
			case 6:
				state = 1;
				tokens[token_num].type = divide;
				tokens[token_num++].value = -1;
				break;
			case 7:
				state = 1;
				tokens[token_num].type = left_brac;
				tokens[token_num++].value = -1;
				break;
			case 8:
				state = 1;
				tokens[token_num].type = right_brac;
				tokens[token_num++].value = -1;
				break;
			default:
				break;
		}
	}
	switch (state) {
		case 2:
			state = 1;
			tokens[token_num].type = num;
			tokens[token_num++].value = atoi(s.substr(left, right - left).c_str());
			break;
		case 8:
			state = 1;
			tokens[token_num].type = right_brac;
			tokens[token_num++].value = -1;
			break;
		default:
			break;
	}
	return token_num;
}

void match(){
	m++;
}

int addexp();
int mulexp();
int factor();

int calc(string s)
{
	get_token(s);
	int ans=addexp();
	return ans;
}

int main()
{
	string s;
	int token_num;
	cin >> s;
	cout<<calc(s)<<endl;
	return 0;
}

int factor(){
	int ans=0;
	if (tokens[m].type==left_brac){
		match();
		ans=addexp();
		match();
	} else {
		ans=tokens[m].value;
		match();
	}
	return ans;
}

int mulexp(){
	int ans=factor();
	while (tokens[m].type==mul||tokens[m].type==divide){
		if (tokens[m].type==mul){
			match();
			ans*=factor();
		} else {
			match();
			ans/=factor();
		}
	}
	return ans;
}

int addexp(){
	int ans=mulexp();
	while (tokens[m].type==add||tokens[m].type==sub){
		if (tokens[m].type==add){
			match();
			ans+=mulexp();
		} else{
			match();
			ans-=mulexp();
		}
	}
	return ans;
}
