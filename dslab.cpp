#include<bits/stdc++.h>
using namespace std;

void projCredits() {
	cout << endl << "::::::::::::::::::::::::::::::::::::::" << endl;
	// cout << "Project: SPLITWISE" << endl;
	// cout << "Made by:" << endl;
	// cout << "\t1. Shaan Grover (19103062)" << endl;
	// cout << "\t2. Anurag Rai (19103065)" << endl;
	// cout << "\t3. Vishruti Chauhan(19103069)" << endl;
	// cout << "::::::::::::::::::::::::::::::::::::::" << endl;
}

class transaction {
	string payer;
	string payee;
	int amount;
public:
	transaction(string payer, string payee, int amount) {
		this->payer = payer;
		this->payee = payee;
		this->amount = amount;
	}

	string getPayer() { return payer; }
	string getPayee() { return payee; }
	int getAmount() { return amount; }

	void displayTr() {
		cout << payer << " -> " << payee << " [" << amount << "]";
	}
};



class settlement {
	string name;
	transaction* trsc[10];
	int count;
	unordered_map<string, int> mp;
public:
	settlement() {
		count = 0;
	}

	settlement(string name) {
		this->name = name;
	}

	void addTransaction(transaction* t) {
		if (count >= 10) {
			cout << "Cannot Add Transaction (Overflow)" << endl;
			return;
		}
		trsc[count++] = t;
		mp[t->getPayer()] -= t->getAmount();
		mp[t->getPayee()] += t->getAmount();
	}

	void display() {
		cout << "Settlement: " << name << endl;
		if(count == 0) {
			cout << "No Transactions present!" << endl;
			return;
		}

		for(int i = 0; i < count; ++i) {
			cout << i+1 << ".) ";
			trsc[i]->displayTr();
			cout << endl;
		}
	}

	void displayMap() {
		for(auto i : mp) {
			cout << i.first << " " << i.second << endl;
		}
	}

	void settlePayment() {
		priority_queue<pair<int, string>> max_pq;
		priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> min_pq;

		for(auto i : mp) {
			if(i.second > 0) {
				max_pq.push({i.second, i.first});
			}
			else if(i.second < 0) {
				min_pq.push({i.second, i.first});
			}
		}

		while(!min_pq.empty()){
			if(max_pq.size()==0)
				break;

			pair<int, string> a = max_pq.top();
			max_pq.pop();
			pair<int,string> b = min_pq.top();
			min_pq.pop();

			if((a.first + b.first) == 0) {
				cout << a.second << " -> " << b.second << " " << a.first << endl;
				mp[a.second]  = 0;
				mp[b.second] = 0;
			}
			else if((a.first + b.first) > 0) {
				int diff = a.first + b.first;
        		mp[a.second] -= diff;
				mp[b.second] = 0;
				if(mp[a.second] != 0)
					max_pq.push({mp[a.second],a.second});
				cout << a.second << " -> " << b.second << " " << diff << endl;
			}
			else {
				mp[b.second] += a.first;
				mp[a.second] = 0;
				min_pq.push({mp[b.second], b.second});				
				cout << a.second << " -> " << b.second << " " << a.first << endl;
			}
		}
		this->displayMap();
	}

	int getNoOfTrnsc() { return count; }
};

void setlMenu() {
	cout << "\n1. Add Transaction" << endl;
	cout << "2. Settle Payments" << endl;
	cout << "3. Exit" << endl;
	cout << "\n=> Enter your Option: ";
}

class User {
	string username;
	string password;
	settlement* setll[5];
	int stllCount;
public:
	User() {
		stllCount = 0;
	}

	User(string username, string password) {
		this->username = username;
		this->password = password;
		stllCount = 0;
	}

	string getUsername() { return username; }

	bool checkPass(string P) {
		if (P == password) 
			return true;
		return false;
	}

	void displaySettlements() {
		if(stllCount == 0) {
			cout << "No Settlements" << endl;
			return;
		}

		for(int i = 0; i < stllCount; ++i) {
			setll[i]->display();
			setll[i]->displayMap();
		}
	}

	void addSettlement() {
		cout << "\nEnter Settlement Name: ";
		string nm;
		cin >> nm;
		settlement* t = new settlement(nm);
		setll[stllCount++] = t;
		
		while(1) {
			setlMenu();
			int opt;
			cin>> opt;
			if(opt == 1) {
				string p1, p2;
				int amt;
				cout << "Payer: ";
				cin >> p1;
				cout << "Payee: ";
				cin >> p2;
				cout << "Amount: ";
				cin >> amt;
				transaction* temp = new transaction(p1, p2, amt);
				setll[stllCount - 1]->addTransaction(temp);
				displaySettlements();
			}
			else if(opt == 2) {
				// Call Splitwise
				setll[stllCount - 1]->settlePayment();
			}
			else {
				break;
			} 
				
		}
	}
};

// Registered Users
User* reg[10];
int cnt = 0;
// ****************

User* authenticate(string usrnm, string pswd) {
	for(int i = 0; i < cnt; ++i) {
		if(reg[i]->getUsername() == usrnm && reg[i]->checkPass(pswd))
			return reg[i];
		cout << "Error!" << endl;
		return NULL;
	}
}

void mainMenu() {
	cout << "\n1. Already a Splitwise User?  Login" << endl;
	cout << "2. Not a Splitwise User?  SignUp" << endl;
	cout << "3. Continue as Guest." << endl;
	cout << "4. Project Credits" << endl;
	cout << "\n=> Enter your Option: ";
}

void dashboardMenu() {
	cout << "\n1. My Settlements" << endl;
	cout << "2. Add New Settlement" << endl;
	cout << "3. Logout" << endl;
	cout << "\n=> Enter your Option: ";
}

void dashboard(User* curr) {
	cout << "\nWelcome " << curr->getUsername() << endl;
	while(1) {
		dashboardMenu();
		int opt; 
		cin >> opt;

		if(opt == 1) {
			curr->displaySettlements();
			break;
		}
		else if(opt == 2) {
			curr->addSettlement();
			break;
		}
		else
			break;
	}
}

void login() {
	string uname;
	string pswd;
	cout << "\nUsername: ";
	cin >> uname;
	cout << "Password: ";
	cin >> pswd;

	User* temp = authenticate(uname, pswd);
	if(temp == NULL) {
		login();
		return;
	}
		
	dashboard(temp);
}

void addUser() {
	string uname;
	string pswd;
	cout << "\nEnter Username: ";
	cin >> uname;
	cout << "Enter Password: ";
	cin >> pswd;

	reg[cnt++] = new User(uname, pswd);

	dashboard(reg[cnt-1]);
}


int main() {
	cout << ":::::::::::::::::::: S P L I T W I S E ::::::::::::::::::::" << endl;
	cout << "\nWelcome to Splitwise, an easy way to settle payments." << endl;

	while (1) {
		mainMenu();
		int opt;
		cin >> opt;

		switch (opt) {
			case 1 : {
				login();
				break;
			}
			case 2 : {
				addUser();
				break;
			}
			case 3 : {
				settlement* guest = new settlement("GUEST");
				while(1) {
					setlMenu();
					int op;
					cin>> op;
					if(op == 1) {
						string p1, p2;
						int amt;
						cout << "Payer: ";
						cin >> p1;
						cout << "Payee: ";
						cin >> p2;
						cout << "Amount: ";
						cin >> amt;
						transaction* temp = new transaction(p1, p2, amt);
						guest->addTransaction(temp);
					}
					else if(op == 2) {
						// Call Splitwise
						guest->settlePayment();
					}
					else {
						break;
					} 					
				}
				break;
			}
			case 4 : {
				projCredits();
				break;
			}
			default : {
				cout << endl << "Enter Valid Option!!" << endl;
				break;
			}
		}
	}

	return 0;
}