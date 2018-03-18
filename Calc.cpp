#include <iostream>
#include <string> // 입력을 스트링으로 받음
#include "Stack_LinkedList.h" // 후위 수식으로 바꾸기 위해 스택 사용
#include <math.h> //pow 함수

using namespace std;

//계산기 인터페이스
class Calc {
public:
	Calc(); // 생성자
	double calculate(string s); // 계산함수
private:
	void postfix(string s); // 후위 수식으로 바꿔줌
	Stack *post; // 후위 수식으로 바뀐 수식을 저장하는 곳
	int *numindex; // 숫자 42와 '+'의 아스키코드 42를 구분하기 위해 숫자의 인덱스를 플래그로 세움(숫자 == 1, 기호 == 0)
	double result; // 윈도우 계산기처럼 이어서 계산하기 위해 이전 계산 결과를 저장
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
	cin.ios_base::sync_with_stdio(false); // 출력 속도 늘리기
	cin.tie(NULL); // 출력 속도 늘리기
	Calc *T = new Calc; // 계산기 클래슷 생성
	string s; // 입력 받을 스트링 객체


	cout << "Want to exit: Y\n";
	cout << "*---------------------------*\n";


	do {
		cout << "Equation = ";
		cin >> s; // 수식 입력 받음
		if (!s.compare("Y"))
			return 0;//Y 입력시 종료
		T->calculate(s);//입력받은 스트링을 계산
	} while (1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//생성자
Calc::Calc() :
	post{ 0 }, result{ 0 } {}


//후위수식으로 바꿔줌
void Calc::postfix(string s) {
	int count = 0;
	int flag=0; // 소수점 플래그(정수 15와 소수 1.5의 저장 방식이 다름)
	double buf=0; // 연산자를 만나기 전까지 스트링으로 된 숫자를 숫자 데이터로 바꾸기 위한 임시 버퍼
	Stack oper; // 후위 수식으로 바꾸기 위해 사용되는 연산자 스택


	post = new Stack; // 후위 수식이 저장되는 스택
	numindex = new int[s.length()]; // 연산자 42와 숫자 42를 구분하기 위한 인덱스


	for (int i = 0; i < s.length(); i++)
		numindex[i] = 0; // numindex 초기화


	if (s[0] < 48 || s[0] >57) { // 입력된 수식이 연산자부터 시작하는지 숫자부터 시작하는지 구분하여 이전 계산 결과를 사용하는지 결정
		post->Push(result);
		numindex[post->size() - 1] = 1;
	}
	result = 0;



	for (int i = 0; i < (int)s.length(); i++) {
		if (s[i] == '.') {
			buf += (double)(s[i + 1] - 48) / 10; // 소수 데이터 저장
			flag = 1; // 소수 플래그 세움
		}
		else if (((48 <= s[i]) && (57 >= s[i]))) {
			if(flag != 1)
				buf = buf * 10 + (double)s[i] - 48; // 숫자 값 저장
			if (i == s.length() - 1) { // 마지막 문자열인지 확인
				post->Push(buf);
				numindex[post->size()-1] = 1;
			}
		}
		else {
			flag = 0;
			if (buf != 0) {
				post->Push(buf);
				numindex[post->size()-1] = 1;
			}
			if (s[i] == ')') {
				while (post->Push(oper.Pop()) != '(') {}
				post->Pop();
			}
			else if (s[i] == '+' || s[i] == '-') {
				while (oper.Read() == '^' || oper.Read() == '*' || oper.Read() == '/' || oper.Read() == '+' || oper.Read() == '-')
					post->Push(oper.Pop());
			}
			else if (s[i] == '*' || s[i] == '/')
				while (oper.Read() == '^' || oper.Read() == '*' || oper.Read() == '/')
					post->Push(oper.Pop());
			else if (s[i] == '^')
				while (oper.Read() == '^')
					post->Push(oper.Pop());
			if(s[i] != ')')
				oper.Push(s[i]);
			buf = 0;
		}
	}



	for (int i = 0; oper.size() != 0; i++) 
		post->Push(oper.Pop());   //연산자 스택 후위수식 스택으로 push
}



//후위 수식으로 바꿔줌
double Calc::calculate(string s) {
	postfix(s);
	Stack k,buf;
	double m, n, p;
	int flag = 0;


	for (int i = 0; post->size(); i++)
		buf.Push(post->Pop());//후위 수식 반대로 들어가있는거 똑바로 다시 넣기



	for (int i = 0; buf.size() != 0; i++) {
		p = buf.Pop();
		if (numindex[i] == 1)
			k.Push(p);
		else {
			m = k.Pop();
			n = k.Pop();
			if (p == '+')
				k.Push(m + n);
			else if (p == '*')
				k.Push(m*n);
			else if (p == '-')
				k.Push(n - m);
			else if (p == '/')
				k.Push(n / m);
			else if (p == '^')
				k.Push(pow(n,m));
			else {
				flag = 1;
				break;
			}
		}
	}



	if (flag == 1)
		cout << "error" << endl;
	else {
		result += k.Pop();
		cout << result << endl;
	}



	delete(post);
	delete(numindex);
	return 0;
}
