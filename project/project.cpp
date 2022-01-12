#include<iostream>
#include<sstream>
#include<string>
#include<conio.h>
#include<fstream>
#include<vector>

using namespace std;
static int wickets = 0;
static int tot_runs = 0;
static int batsmen_A = 0;
static int batsmen_B = 0;
static int first = 0; //ASSUMED
static int tot_overs = 50;
static float proability = 0;
static int required_runs = 0;


class second
{
	vector<int>v;
	vector<string>v1, v2;
	int score_index, wicket_index, over_index, size, count, striker_index, name1_index, name2_index;
	float overs;
	string line_1, data;
public:
	second()
	{
		name1_index = 5;
		name2_index = 6;
		size = 7;
		score_index = 1;
		wicket_index = 2;
		over_index = 0;
		striker_index = 3;
		count = 0;
		overs = 0;
	}
	void get_from_file(float num)
	{
		string* arr;
		arr = new string[size];
		ifstream file_1;
		file_1.open("my_work.csv");
		if (file_1.is_open())
		{
			while (overs != num)
			{
				getline(file_1, line_1);
				stringstream s(line_1);
				count = 0;
				while (getline(s, data, ','))
				{
					arr[count] = data;
					count++;
				}
				tot_runs = tot_runs + stoi(arr[score_index]);
				overs = stof(arr[over_index]);
				if (arr[wicket_index] == "runout" || arr[wicket_index] == "caught" || arr[wicket_index] == "bowled" || arr[wicket_index] == "stump" || arr[wicket_index] == "hitwicket")
				{
					wickets++;
				}
				if (arr[striker_index] == "batsmenA")
				{
					if (arr[wicket_index] == "runout" || arr[wicket_index] == "caught" || arr[wicket_index] == "bowled" || arr[wicket_index] == "stump" || arr[wicket_index] == "hitwicket")
					{
						//cout<<"LLL FOR A"<<endl;
						generate_scoreboard(batsmen_A, arr[name1_index]);
						batsmen_A = 0;
					}
					else
					{
						//cout<<arr[wicket_index]<<endl;
						batsmen_A = batsmen_A + stoi(arr[score_index]);
					}
				}
				else if (arr[striker_index] == "batsmenB")
				{
					if (arr[wicket_index] == "runout" || arr[wicket_index] == "caught" || arr[wicket_index] == "bowled" || arr[wicket_index] == "stump" || arr[wicket_index] == "hitwicket")
					{
						//	cout<<"LLL"<<endl;
						generate_scoreboard(batsmen_B, arr[name2_index]);
						batsmen_B = 0;
					}
					else
					{
						//	cout<<arr[wicket_index]<<endl;
						batsmen_B = batsmen_B + stoi(arr[score_index]);
					}
				}
			}
			cout << "CURRENT SCORE:" << tot_runs << endl;
			cout << "CURRENT OVERS:" << overs << endl;
			cout << "WICKETS DOWN:" << wickets << endl;
			cout << "\n****CURRENT BATSMENS****\n" << endl;
			cout << arr[name1_index] << ": " << batsmen_A << endl;
			cout << arr[name2_index] << ": " << batsmen_B << endl;
			display();
			required_runs = first - tot_runs;
			if (required_runs > 0)
			{
				predict(arr);
			}
			else
			{
				cout << "MATCH ENDS" << endl;
			}
		}
		else
		{
			cout << "FILE NOT OPENED" << endl;
		}
		file_1.close();
	}
	void predict(string* ptr)
	{
		vector<int> t, t1;
		int remain_overs = tot_overs - overs;
		float required_run_rate = required_runs / remain_overs;
		int remain_balls = remain_overs * 6;
		t = record(ptr[name1_index]);
		t1 = record(ptr[name2_index]);
		float scoring_ability = (t[1] + t1[1]) / 2;
		scoring_ability = (scoring_ability / required_run_rate) * 10;
		proability = scoring_ability * 3;
		if (t[0] >= 30)
		{
			proability = proability + 10;
		}
		if (t1[0] >= 30)
		{
			proability = proability + 10;
		}
		if (batsmen_A > 30)
		{
			proability = proability + 10;
		}
		if (batsmen_B > 30)
		{
			proability = proability + 10;
		}
		proability = proability - (wickets * 2);
		cout << "\n******ASKING CONDITION******\n" << endl;
		cout << "REQUIRED RUNS: " << required_runs << endl;
		cout << "REMAINING BALLS: " << remain_balls << endl;
		cout << "\n*****WINNING PROABILITY AT CURRENT SITUATION*****" << endl;
		cout << proability << "%" << endl;
		cout << "\n\n";
		for (int i = 0; i < proability; i = i + 3)
		{
			cout << "\xB2";
		}
	}
	void bar_graph(float num)
	{
		int largest = 0;
		int sum = 0;
		float counter = 1;
		vector<int>k;
		ifstream file_2;
		file_2.open("my_work.csv");
		if (file_2.is_open())
		{
			while (overs <= num)
			{
				string* bar_arr;
				bar_arr = new string[size];
				getline(file_2, line_1);
				stringstream s1(line_1);
				count = 0;
				while (getline(s1, data, ','))
				{
					bar_arr[count] = data;
					count++;
				}
				overs = stof(bar_arr[over_index]);
				if (stof(bar_arr[over_index]) <= counter)
				{
					sum = sum + stoi(bar_arr[score_index]);
				}
				else
				{
					k.push_back(sum);
					counter++;
					sum = 0;
				}
			}
			for (int i = 0; i < k.size(); i++)
			{
				if (k[i] > largest)
				{
					largest = k[i];
				}
			}
			cout << "\n******BAR CHART OF RUNS SCORED PER OVER****\n" << endl;
			for (int i = 0; i < k.size(); i++)
			{
				cout << "[" << (i + 1) << "]";
				cout << "  ";
				for (int j = 0; j < k[i]; j++)
				{
					cout << "\xB2";
					cout << " ";
				}
				cout << "\n" << endl;
			}
			cout << "RUNS ";
			for (int i = 0; i < largest; i++)
			{
				cout << i + 1;
				cout << " ";
			}
		}
		else
		{
			cout << "FILE NOT OPENED" << endl;
		}
		file_2.close();
	}

	void create_file()
	{
		ofstream os("INFO.txt", ios::app);
	}
	vector<string> read_file()
	{
		ifstream is("INFO.txt", ios::in);
		if (is.is_open())
		{
			istream_iterator<string> is_it(is);
			istream_iterator<string> eos;
			copy(is_it, eos, back_inserter(v2));
		}
		else
		{
			cout << "FILE NOT OPEN" << endl;
		}
		return v2;
	}
	vector<int> record(string name)
	{
		int i = 0;
		vector<int> s2;
		vector<string> s;
		s = read_file();
		for (i = 0; i < s.size(); i++)
		{
			if (s[i] == name)
			{
				int temp = 0;
				i = i + 1;
				while (s[i] != "Rate")
				{
					temp = temp + stoi(s[i]);
					i++;
				}
				temp = temp / 3;
				s2.push_back(temp);
				int rate_new = stoi(s[i + 1]);
				s2.push_back(rate_new);
				break;
			}
		}
		return s2;
	}
	void generate_scoreboard(int runs, string player_name)
	{
		v.push_back(runs);
		v1.push_back(player_name);
	}
	void display()
	{
		cout << endl;
		cout << "****PLAYERS DEPART******" << endl;
		for (int i = 0; i < v.size(); i++)
		{
			cout << v1[i] << ":" << v[i] << endl;
		}
		cout << "\n\n";
	}
	
};





void Prediction_before_match()
{
	cout << "\n\n\t\t\t ----- WELCOME TO Prediction Before Match ----- \n\n";
	ifstream MyExcelFile;
	MyExcelFile.open("headtohead.csv");

	string t_name;
	cout << "\nEnter First Team name: ";
	cin >> t_name;
	string line;
	string opp;
	int count = 0;


	getline(MyExcelFile, line);
	stringstream s(line);
	while (!MyExcelFile.eof())
	{
		getline(s, opp, ',');
		count++;
		if (opp == t_name)
		{
			break;
		}
	}


	string line2;

	string t2_name;
	cout << "\nEnter Second Team name: ";
	cin >> t2_name;

	string opp2;
	string opp3;
	int win1;
	int win2;
	int count2 = 0;

	while (!MyExcelFile.eof())
	{
		getline(MyExcelFile, line2);
		stringstream s(line2);
		getline(s, opp2, ',');
		if (opp2 == t2_name)
		{

			int i = 1;
			while (i != count)
			{
				getline(s, opp3, ',');
				i++;
			}
			break;
		}
	}

	MyExcelFile.close();


	stringstream geek(opp3);
	geek >> win1;


	string t3_name = t2_name;
	count = 0;
	string line3;
	string line4;
	string opp4;
	string opp5;
	string opp6;

	MyExcelFile.open("headtohead.csv");

	getline(MyExcelFile, line3);
	stringstream s3(line3);

	while (!MyExcelFile.eof())
	{
		getline(s3, opp4, ',');
		count++;
		if (opp4 == t3_name)
		{
			break;
		}
	}



	string t4_name = t_name;

	while (!MyExcelFile.eof())
	{
		getline(MyExcelFile, line4);
		stringstream s4(line4);
		getline(s4, opp5, ',');
		if (opp5 == t4_name)
		{

			int i = 1;
			while (i != count)
			{
				getline(s4, opp6, ',');
				i++;
			}
			break;
		}
	}
	MyExcelFile.close();

	stringstream geek2(opp6);
	geek2 >> win2;

	int total = win1 + win2;

	cout << "\nHead To Head:";

	cout << "\n\nTotal Matches: ";
	cout << total;

	cout << "\n" << t_name << ": " << win2;
	cout << "\n" << t2_name << ": " << win1;


	cout << "\n\nWin percrentage of " << t2_name << ": ";
	int p = win1 * 100;
	cout << (p / total) << "%";

	int pe = p / total;


	cout << "\n\n";

	for (int i = 0; i < pe; i = i + 3)
	{
		cout << "\xB2";
	}

	cout << "\n\nWin percrentage of " << t_name << ": ";
	int p2 = win2 * 100;
	cout << (p2 / total) << "%";

	int pe2 = p2 / total;


	cout << "\n\n";

	for (int i = 0; i < pe2; i = i + 3)
	{
		cout << "\xB2";
	}

}

void score_prediction()
{
	cout << "\n\n\t\t\t ----- WELCOME TO SCORE PREDICTION ----- \n\n";
	ifstream MyExcelFile;
	cout << "\n\nEnter File name:";
	string g_name;
	cin >> g_name;
	MyExcelFile.open(g_name);
	string overs;
	string run1;
	string run2;
	int i = 0;
	float Overs;
	int r1;
	int r2;
	float runs1 = 0;
	float runs2 = 0;
	string line;
	int run = 0;
	int count = 0, count2 = 0;

	cout << "\n\nEnter the over number:" << endl;
	float over;
	cin >> over;

	while (!MyExcelFile.eof())
	{
		getline(MyExcelFile, line);
		stringstream s(line);
		getline(s, overs, ',');
		count++;
		stringstream geek0(overs);
		geek0 >> Overs;
		if (Overs == over)
		{
			break;
		}

		getline(s, run1, ',');
		stringstream geek(run1);
		geek >> r1;
		runs1 = runs1 + r1;

		getline(s, run2, ',');
		stringstream geek2(run2);
		geek2 >> r2;
		runs2 = runs2 + r2;
		run = run + r1 + r2;
		if (count == 6)
		{
			count2++;
			cout << "Over" << count2 << "  ";

			for (int j = 1; j <= run; j++)
			{
				cout << " \xB2";
			}
			cout << "\n\n";
			count = 0;
			run = 0;
		}

	}
	MyExcelFile.close();

	cout << "\nTotal Socre " << runs1 + runs2 << " till " << over << " Overs " << endl;
	float total_socre_Till_given_over;
	total_socre_Till_given_over = runs1 + runs2;
	float run_rate;
	run_rate = total_socre_Till_given_over / over;
	cout << "\nRun Rate: " << run_rate << endl;

	float remaining = 50 - over;
	float j = 0;
	int predicted_Score[4] = { 0,0,0 };
	for (i = 0; i < 4; i++)
	{
		run_rate = run_rate + i;
		predicted_Score[i] = (run_rate * remaining) + total_socre_Till_given_over;
		cout << "\npredicted Score " << predicted_Score[i] << " at the Run rate of " << run_rate << endl;
	}

}



struct node
{
	int data;
	node* left = NULL, * right = NULL;
};
class tree
{
	node* head;
public:
	tree()
	{
		head = NULL;
	}

	~tree()
	{

	}

	node* insert(node* temp, int value)
	{

		if (temp == NULL)
		{
			node* tmp = new node;
			tmp->data = value;

			tmp->left = NULL;
			tmp->right = NULL;

			return tmp;
		}
		else if (value > temp->data)
		{
			temp->right = insert(temp->right, value);

		}
		else if (value < temp->data)
		{
			temp->left = insert(temp->left, value);
		}
		return temp;
	}

	void search(node* temp, int value)
	{
		if (temp->data == value)
		{
			cout << " found" << endl;
			return;
		}
		if (value > temp->data)
		{
			search(temp->right, value);

		}
		else if (value < temp->data)
		{
			search(temp->left, value);
		}
		return;
	}
	void inorder(node* root)
	{
		if (root == NULL)
		{
			return;
		}
		inorder(root->left);
		cout << " " << root->data;
		inorder(root->right);

	}

	int win(node* root, int value, int won)
	{
		if (root == NULL)
		{
			return won;
		}

		won = win(root->left, value, won);
		if (root->data > value && root->data < (value + 20))
		{
			won++;
		}
		won = win(root->right, value, won);
	}

	int lost(node* root, int value, int loss)
	{
		if (root == NULL)
		{
			return loss;
		}
		loss = lost(root->left, value, loss);
		if (root->data < value && root->data >(value - 20))
		{
			loss++;
		}
		loss = lost(root->right, value, loss);
	}
};

int match_prediction()
{
	cout << "\n\n\t\t\t ----- WELCOME TO MATCH PREDICTION ----- \n\n";
	tree w, l;
	ifstream is;
	cout << "\nEnter Ground name:";
	string g_name;
	cin >> g_name;
	is.open(g_name);
	string line, type;
	int scores, i = 0, j = 0;
	string score;
	node* root = NULL;
	node* root2 = NULL;


	while (!is.eof())
	{
		getline(is, line);
		stringstream s(line);
		getline(s, score, ',');
		stringstream s1(score);
		s1 >> scores;
		getline(s, type, ',');
		if (type == "won")
		{
			if (i == 0)
			{
				root = w.insert(root, scores);
				i++;
			}
			else
			{
				w.insert(root, scores);
			}
		}
		else
		{
			if (j == 0)
			{
				root2 = l.insert(root2, scores);
				j++;
			}
			else
			{
				l.insert(root2, scores);
			}
		}

	}
	is.close();

	cout << endl;

	int t_score;
	cout << "\nEnter Total Score of First inning: ";
	cin >> t_score;


	float won = w.win(root, t_score, 0);
	float loss = l.lost(root2, t_score, 0);

	int percentage = 0;
	float t = (won / (won + loss));
	percentage = t * 100;
	cout << "\nWin Percentage: " << percentage << "%";


	cout << "\n\n";
	for (int i = 0; i < percentage; i = i + 3)
	{
		cout << "\xB2";
	}

	int percentage2 = 100 - percentage;

	cout << "\nLoss Percentage: " << percentage2 << "%";

	cout << "\n\n";
	for (int i = 0; i < percentage2; i = i + 3)
	{
		cout << "\xB2";
	}

	return t_score;
}

void Title_Page()
{
	system("cls");
	system("color f2");
	cout << "\n\t                       \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
	cout << "\n\t                       \xB2\xB2                                 \xB2\xB2";
	cout << "\n\t                       \xB2\xB2     @@@@@@@@@@@@@@@@@@@@@@@     \xB2\xB2";
	cout << "\n\t                       \xB2\xB2     @                     @     \xB2\xB2";
	cout << "\n\t                       \xB2\xB2     @      WELCOME TO     @     \xB2\xB2";
	cout << "\n\t                       \xB2\xB2     @                     @     \xB2\xB2";
	cout << "\n\t                       \xB2\xB2     @        WINNER       @     \xB2\xB2";
	cout << "\n\t                       \xB2\xB2     @         AND         @     \xB2\xB2";
	cout << "\n\t                       \xB2\xB2     @        SCORE        @     \xB2\xB2";
	cout << "\n\t                       \xB2\xB2     @       PREDICTOR     @     \xB2\xB2";
	cout << "\n\t                       \xB2\xB2     @                     @     \xB2\xB2";
	cout << "\n\t                       \xB2\xB2     @@@@@@@@@@@@@@@@@@@@@@@     \xB2\xB2";
	cout << "\n\t                       \xB2\xB2                                 \xB2\xB2";
	cout << "\n\t                       \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n";
	cout << "\n\n-----------------------------------" << endl;
	cout << "PRESS ANY KEY TO CONTINUE......." << endl;
	cout << "-----------------------------------" << endl;
	_getch();
}


int main()
{
	Title_Page();

	system("color f5");
	char opt;

	do
	{
		int choice;
		int t_score = 0;
		system("cls");
		cout << endl << "\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  WELCOME TO WINNING AND SCORE PREDICTOR SYSTEM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n";
		cout << "\n\n\t\t\t1: PREDICTION BEFORE MATCH \n\t\t\t2: SCORE PREDICTION DURING FIRST INNING \n\t\t\t3: MATCH PREDICTION AFTER FIRST INNING \n";
		cout << "\n\t               \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n";
		cout << "\n\n\t\t\tENTER YOUR CHOICE: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("cls");
			Prediction_before_match();
			break;

		case 2:

			system("cls");
			score_prediction();
			break;

		case 3:
			system("cls");
			t_score = match_prediction();
			break;
		}

		first = t_score;


		cout << "\n\nDo you want Predict More in First Inning(Y/N)";
		cin >> opt;
	} while (opt == 'Y' || opt == 'y');


	system("cls");
	cout << "\n\nNow Second Inning Prediction";

	second s1;
	float num;
	cout << "\n\nLET CURRENT SITUATION IS(Enter The Over Number of Second Inning):" << endl;
	cin >> num;
	s1.get_from_file(num);
	s1.display();
	//s1.create_file();
	s1.bar_graph(num);

}