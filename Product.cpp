#include<iostream>
#include<string>

using namespace std;

class Product
{
private:
	int id;
	char* name;
	char* description;
	double price;
	double* priceHistory;
	int priceHistoryCount;


	//constructor
public:
	Product()
	{

	}
	 
	Product(int _id, const char* _name, const char* _description, double _price, double* _priceHistory, int _priceHistoryCount)
	{
		this->id = _id;
		this->name = new char[strlen(_name) + 1];
		strcpy_s(this->name, strlen(_name) + 1, _name);

		this->description = new char[strlen(_description) + 1];
		strcpy_s(this->description, strlen(_description) + 1, _description);

		this->price = _price;

		this->priceHistory = new double[_priceHistoryCount];
		for (int i = 0; i < _priceHistoryCount; i++)
		{
			this->priceHistory[i] = _priceHistory[i];
		}

		this->priceHistoryCount = _priceHistoryCount;
	}


	//constructor de copiere
	Product(const Product& product)
	{
		this->id = product.id;

		this->name = new char[strlen(product.name) + 1];
		strcpy_s(this->name, strlen(product.name) + 1, product.name);

		this->description = new char[strlen(product.description) + 1];
		strcpy_s(this->description, strlen(product.description) + 1, product.description);

		this->price = product.price;
		
		this->priceHistory = new double[product.priceHistoryCount];
		for (int i = 0; i < product.priceHistoryCount; i++)
		{
			this->priceHistory[i] = product.priceHistory[i];
		}
		

	}


	//all setters
	void set_name(char* _name)
	{
		this->name = _name;
	}

	void set_description(char* _description)
	{
		this->description = _description;
	}

	void set_priceHistory(double* _priceHistory, int _priceHistoryCount)
	{	
		this->priceHistoryCount = _priceHistoryCount;

		this->priceHistory = new double[_priceHistoryCount];
		for (int i = 0; i < _priceHistoryCount; i++)
		{
			this->priceHistory[i] = _priceHistory[i];
		}
	}


	//all getters
	//.....
	int get_id() { return this->id; }
	char* get_name() { return this->name; }
	char* get_description() { return this->description; }
	double get_price() { return this->price; }
	double* get_priceHistory() { return this->priceHistory; }


	double getPriceAverage()
	{	
		if (priceHistory)
		{
			int sum = 0;
			for (int ind = 0; ind < priceHistoryCount; ind++)
			{
				sum += priceHistory[ind];
			}

			return sum / priceHistoryCount;

		}
		return 0;
	}

	int main() 
	{
		/*Product p0;

		p0.id = 1;

		p0.name = new char[20];
		strcpy_s(p0.name, 20, "MyProduct");

		p0.description = new char[20];
		strcpy_s(p0.description, 20, "really cool");

		p0.price = 100;

		double priceHistory[4] = { 100, 130, 140, 120 };
		p0.set_priceHistory(priceHistory, 4);
		*/

		int priceHistoryCount = 4;
		double priceHistory[4] = { 100, 130, 140, 120 };
		Product p0(1, "MyProduct", "really cool", 100.00, priceHistory, 4);

		return 0;
		
	}

	//destructor
	~Product() {
		delete[] name;
		delete[] description;
		delete[] priceHistory;
	}

};

