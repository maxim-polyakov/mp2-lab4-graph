#pragma once

class Shared {
private:
	int *parent;
	int *height;
	int n;
	bool validIndex(int i);
public:
	Shared(int n);
	~Shared();

	void singleton(int i);
	void association(int i, int j);
	int defineSet(int i);
	int getSetSize(int i);
};


//___________________________________________________________________________________________


Shared::Shared(int n)
{
	parent = new int[n];
	for (int i = 0; i < n; i++)
		parent[i] = -1;
	height = new int[n];
	this->n = n;
}

Shared::~Shared()
{
	delete[] parent;
	delete[] height;
}

bool Shared::validIndex(int i)
{
	if ((i < 0) || (i >= n))
		return false;
	else
		return true;
}

void Shared::singleton(int i)
{
	if (!validIndex(i))
		throw "Неверный номер!";
	if (parent[i] != -1)
		return;
	parent[i] = i;
	height[i] = 0;
}

void Shared::association(int i, int j)
{
	if ((!validIndex(i)) || (!validIndex(j)))
		throw "Неверный номер!";
	if ((parent[i] == -1) || (parent[j] == -1))
		throw "Пусто!";
	if (parent[i] != i)
		i = defineSet(i);
	if (parent[j] != i)
		j = defineSet(j);
	if (height[i] > height[j])
		parent[j] = i;
	else if (height[i] < height[j])
		parent[i] = j;
	else {
		parent[j] = i;
		height[i]++;
	}
}

int Shared::defineSet(int i)
{
	if (!validIndex(i))
		throw "Неверный номер!";
	if (parent[i] == -1)
		return -1;
	while (parent[i] != i)
		i = parent[i];
	return i;
}

int Shared::getSetSize(int i)
{
	int count = 0;
	int local_parent = defineSet(i);
	for (int i = 0; i < n; i++)
		if (parent[i] = local_parent)
			count++;
	return count;
}