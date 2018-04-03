#include <fstream>

using namespace std;

struct Array
{
	int Data;
	int Location;
};

void Input(ifstream &fi, int* &arr, int& length)
{
	fi >> length;
	arr = new int[length];
	for (int i = 0;i < length;i++)
	{
		fi >> *(arr + i);
	}
}

void Sort(Array* &a, int left, int right)
{
	int i = left;
	int j = right;
	int x = (a + (i + j) / 2)->Data;
	while (i < j)
	{
		while (((a + i)->Data) < x) i++;
		while (((a + j)->Data) > x) j--;
		if (i <= j)
		{
			Array t = *(a + i);
			*(a + i) = *(a + j);
			*(a + j) = t;
			i++;
			j--;
		}
	}
	if (i < right) Sort(a, i, right);
	if (left < j) Sort(a, left, j);
}

void LinearSearch(ofstream &fo, int* &arr, int length, int x)
{
	int count = 0;
	for (int i = 0;i < length;i++)
	{
		if (*(arr + i) == x)
		{
			fo << i << " ";
			count++;
		}
	}
	if (count == 0)
		fo << -1;
}

void SentinelLinearSearch(ofstream &fo, int* &arr, int x)
{
	for (int i=0;;i++)
	{
		if (*(arr + i) == x)
		{
			fo << i;
			return;
		}
	}
	fo << -1;
}

void BinarySearch(ofstream &fo, Array* &a, int length, int x)
{
	int left = 0;
	int right = length - 1;
	while (left != right)
	{
		int m = (left + right) / 2;
		if ((a + m)->Data > x)
		{
			right = m - 1;
		}
		else if ((a + m)->Data < x)
		{
			left = m + 1;
		}
		else
		{
			fo << (a + m)->Location << " ";
			int i = m - 1;
			while ((a + i)->Data == x)
			{
				fo << (a + i)->Location << " ";
				i--;
			}

			i = m + 1;
			while ((a + i)->Data == x)
			{
				fo << (a + i)->Location << " ";
				i++;
			}
			return;
		}
	}
	fo << -1;
}

int main(char argc, char* argv[])
{
	int tt = atoi(argv[1]);	
	int x = atoi(argv[2]);
	ifstream fi;
	fi.open(argv[3], ios::in);
	ofstream fo;
	fo.open(argv[4], ios::out);

	int* arr;
	int length;

	Input(fi, arr, length);
	if (tt == 1)
	{
		LinearSearch(fo, arr, length, x);
	}
	else if (tt == 2)
	{
		SentinelLinearSearch(fo, arr, x);
	}
	else
	{
		Array *a = new Array[length];
		
		for (int i = 0;i < length;i++)
		{
			
			(a + i)->Data= *(arr + i);
			(a + i)->Location = i;
		}
		Sort(a, 0, length - 1);
		BinarySearch(fo, a, length, x);
	}
	fi.close();
	fo.close();
}