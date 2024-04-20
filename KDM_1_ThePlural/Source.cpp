#include "iostream"
#include <iomanip>
#include <windows.h>

using namespace std;

void CheckData(int&);

class Plural {
private:
	int n;
	int* plural;

public:
	Plural();
	Plural(const int&);
	void SetDataPlural(const int&);
	void SetSize();
	void Clear();
	void ShowInfo();
	bool FindElement(const int&);
	void Section(Plural&, Plural&);
	void Union(Plural&, Plural&);
	void Difference(Plural&, Plural&);
	void SymmetricalDifference(Plural&, Plural&);
	void BinaryRelationMatrix(Plural&);
	void ShellSort(int*, int*);
	friend void CheckData(int&);
	~Plural() { delete[] this->plural; }
};

/**
 * @brief Конструктор за замовчуванням класу Plural
*/
Plural::Plural() {
	
	this->n = 0;
	this->plural = nullptr;
}

/**
 * @brief Параметричний конструктор класу Plural
 * @param n Кількість елементів множини
*/
Plural::Plural(const int& n) {
	
	this->n = n;
	plural = new int[this->n];
}

/**
 * @brief Метод, який реалізує додавання додаткового елемента до множини
*/
void Plural::SetSize() {

	int* tmp = new int[this->n];

	if (this->plural != nullptr) {
		for (int i = 0; i < this->n - 1; i++) {
			tmp[i] = this->plural[i];
		}
		delete[] this->plural;
	}
	this->plural = tmp;
}

/**
 * @brief Метод, який очищає множину 
*/
void Plural::Clear() {

	this->n = 0;
	delete[] this->plural;
	this->plural = nullptr;
}

/**
 * @brief Метод, який реалізує введення елементів до множини 
 * @param n Кількість елементів множини
*/
void Plural::SetDataPlural(const int& n) {

	int tmp_x;

	this->n = n;
	plural = new int[this->n];
	for (int i = 0; i < this->n; i++) {
		cout << "Enter the plural element #" << i << ": ";
		do {
			cin >> tmp_x;
			CheckData(tmp_x);
			if (this->FindElement(tmp_x)) cerr << "Find dublicate, please Re-enter" << endl;
		} while (this->FindElement(tmp_x));
		this->plural[i] = tmp_x;
	}
	this->ShellSort(this->plural, &this->n);
}

/**
 * @brief Метод, який виводить в консоль елементи множини
*/
void Plural::ShowInfo() {

	cout << "{ ";
	for (int i = 0; i < this->n; i++) {
		cout << this->plural[i];
		if (i + 1 != this->n) cout << ", ";
	}
	cout << " }\n";
}

/**
 * @brief Метод, який перевіряє присутність елемента в множинні
 * @param x Елемент для пошуку
 * @return True - якщо елемент знайдено інакше false
*/
bool Plural::FindElement(const int& x) {

	if (this->plural == nullptr) return false;
	for (int i = 0; i < this->n; i++) {
		if (this->plural[i] == x) return true;
	}

	return false;
}

/**
 * @brief Метод, який знаходить переріз двох числових множин
 * @param plr1 Перша числова множина
 * @param plr2 Друга числова множина
*/
void Plural::Section(Plural& plr1, Plural& plr2) {
	
	this->Clear();
	for (int i = 0; i < plr1.n; i++) {
		if (plr1.FindElement(plr1.plural[i]) && plr2.FindElement(plr1.plural[i])) {
			this->n++;
			this->SetSize();
			this->plural[this->n - 1] = plr1.plural[i];		
		}
	}
	this->ShellSort(this->plural, &this->n);
}

/**
 * @brief Метод, який знаходить об'єднання двох числових множин
 * @param plr1 Перша числова множина
 * @param plr2 Друга числова множина
*/
void Plural::Union(Plural& plr1, Plural& plr2) {

	this->Clear();
	for (int i = 0; i < plr1.n; i++) {
		if (!this->FindElement(plr1.plural[i])) {
			this->n++;
			this->SetSize();
			this->plural[this->n - 1] = plr1.plural[i];
		}
	}
	for (int i = 0; i < plr2.n; i++) {
		if (!this->FindElement(plr2.plural[i])) {
			this->n++;
			this->SetSize();
			this->plural[this->n - 1] = plr2.plural[i];
		}
	}
	this->ShellSort(this->plural, &this->n);
}

/**
 * @brief Метод, який знаходить різницю двох числових множин
 * @param plr1 Перша числова множина
 * @param plr2 Друга числова множина
*/
void Plural::Difference(Plural& plr1, Plural& plr2) {

	this->Clear();
	for (int i = 0; i < plr1.n; i++) {
		if (plr1.FindElement(plr1.plural[i]) && !plr2.FindElement(plr1.plural[i])) {
			this->n++;
			this->SetSize();
			this->plural[this->n - 1] = plr1.plural[i];
		}
	}
	this->ShellSort(this->plural, &this->n);
}

/**
 * @brief Метод, що знаходить симетричну різницю двох числових множин
 * @param plr1 Перша числова множина
 * @param plr2 Друга числова множина
*/
void Plural::SymmetricalDifference(Plural& plr1, Plural& plr2) {

	this->Clear();
	for (int i = 0; i < plr1.n; i++) {
		if (plr1.FindElement(plr1.plural[i]) && !plr2.FindElement(plr1.plural[i])) {
			this->n++;
			this->SetSize();
			this->plural[this->n - 1] = plr1.plural[i];
		}
	}
	for (int i = 0; i < plr2.n; i++) {
		if (plr2.FindElement(plr2.plural[i]) && !plr1.FindElement(plr2.plural[i])) {
			this->n++;
			this->SetSize();
			this->plural[this->n - 1] = plr2.plural[i];
		}
	}
	this->ShellSort(this->plural, &this->n);
}

/**
 * @brief Метод, який знаходить матрицю бінарного відношення
 * @param plr Числова множина
*/
void Plural::BinaryRelationMatrix(Plural& plr) {

	if (this->n == 0 || plr.n == 0) {
		cout << "One of the sets is empty";
	}
	else {
		cout << "____|";
		for (int j = 0; j < plr.n; j++) {
			cout << setw(4) << setfill('_') << left << plr.plural[j];
		}
		cout << endl;
		for (int i = 0; i < this->n; i++) {
			cout << setw(4) << setfill(' ') << right << this->plural[i] << '|';
			for (int j = 0; j < plr.n; j++) {
				if (this->FindElement(this->plural[i]) && plr.FindElement(plr.plural[j]) && abs(this->plural[i] - plr.plural[j]) < 2) {
					cout << setw(4) << left << "1";
				}
				else cout << setw(4) << left << "0";
			}
			cout << endl;
		}
	}
}

/**
 * @brief Реалізація алгоритму сортування Шелла для змінних типу int
 * @param mas Масив типу int, який потрібно відсортувати
 * @param n Кількість елементів масиву
*/
void Plural::ShellSort(int* mas, int* n) {
	
	int buf;

	//cout << "Shell Sorting is in progress..." << endl;
	for (int step = *n / 2; step > 0; step /= 2) {
		for (int i = step; i < *n; i++) {
			buf = mas[i];
			int j;
			for (j = i; j >= step && buf < mas[j - step]; j -= step) {
				mas[j] = mas[j - step];
			}
			mas[j] = buf;
		}
	}
}

/**
 * @brief Функція, яка перевіряє правильність введення даних користувачем
 * @param x Данні для перевірки типу int
*/
void CheckData(int& x) {

	cin.ignore(666, '\n');
	while (true) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(666, '\n');
			cerr << "You enter wrong data! Please enter correct data: \n";
			cout << "Enter int data: ";
			cin >> x;
			cin.ignore(666, '\n');
		}
		else break;
	}
}

int main() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WCHAR union_symbol[] = L"∪";
	WCHAR section_symbol[] = L"∩";
	WCHAR symdif_symbol[] = L"∆"; 
	WCHAR cartesprod_symbol[] = L"×";
	int work = 1;
	int tmp_a, tmp_b;
	Plural a, b, c;

	while (work != 0) {
		cout << "Enter the size of plural A: "; do { cin >> tmp_a; CheckData(tmp_a); if (tmp_a < 0) cout << "Min size of plural = 0\n"; } while (tmp_a < 0); a.SetDataPlural(tmp_a);
		cout << "Enter the size of plural B: "; do { cin >> tmp_b; CheckData(tmp_b); if (tmp_b < 0) cout << "Min size of plural = 0\n"; } while (tmp_b < 0); b.SetDataPlural(tmp_b);
		cout << "\n______________You ENTER______________:" << endl;
		cout << setw(12) << "The plural A: "; a.ShowInfo();
		cout << setw(12) << "The plural B: "; b.ShowInfo();
		cout << "\n______________Result______________:" << endl;
		cout << "A "; WriteConsoleW(hConsole, section_symbol, wcslen(section_symbol), NULL, NULL); cout << " B : "; c.Section(a, b); c.ShowInfo();
		cout << "A "; WriteConsoleW(hConsole, union_symbol, wcslen(union_symbol), NULL, NULL); cout << " B : "; c.Union(a, b); c.ShowInfo();
		cout << "A \\ B : "; c.Difference(a, b); c.ShowInfo();
		cout << "A "; WriteConsoleW(hConsole, symdif_symbol, wcslen(symdif_symbol), NULL, NULL); cout << " B : "; c.SymmetricalDifference(a, b); c.ShowInfo();
		cout << "\n______________Matrix of binary relation______________:" << endl;
		cout << "A "; WriteConsoleW(hConsole, cartesprod_symbol, wcslen(cartesprod_symbol), NULL, NULL); cout << " B (|a - b| < 2):" << endl; 
		a.BinaryRelationMatrix(b);

		if (work != 0) {
			cout << "\nRetry? 1 - yes / 0 - not" << endl;
			cin >> work;
			CheckData(work);
		}
	}

	return 0;
}