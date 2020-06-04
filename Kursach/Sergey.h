#pragma once

#include <string>
#include <limits>
#include <cstdlib>
#include <fstream>
#include "List.h"

struct Network
{
	void read();
	void read(string text);

	void addNode(string name);

	void addChannel(string S, string T, int weight);

	void print();

	bool contains(string name);

	int Algorhytm(string S, string T);
	int Algorhytm(unsigned int S, unsigned int T);

private:

	void addChannel(unsigned int S, unsigned int T, int weight);

	unsigned int stoindex(string input);

	struct Node
	{
		struct Channel
		{
			Node* T;
			int capacity;
			int leftover;

			Channel(Node* T = nullptr, unsigned int weight = NULL)
			{
				this->T = T;
				this->capacity = weight;
				this->leftover = weight;
			}
		};

		void addChannel(Channel* addChannel)
		{
			this->channels.push_back(addChannel);
		};

		string name;
		List<Channel*> channels;

		Node* previous;
		int flow;

		Node(string name = "")
		{
			this->name = name;
			this->previous = nullptr;
			this->flow = 0;
		}
	};

	List<Node*> network;
};

void Network::read()
{
	ifstream file;
	file.open("input.txt");
	file.unsetf(ios::skipws);

	while (!file.eof())
	{
		string tempS;
		char tempC;
		file >> tempC;
		bool unexpected = false;
		while (tempC != ';')
		{
			if (tempC == '\n' || file.eof())
			{
				unexpected = true;
				break;
			}
			tempS += tempC;
			file >> tempC;
		}
		if (unexpected == true)
			continue;

		string S = tempS;
		if (S.size() == 0)
			throw exception("no S name");
		if (contains(S) == false)
			addNode(S);
		tempS.clear();

		file >> tempC;
		while (tempC != ';')
		{
			if (tempC == '\n' || file.eof())
			{
				unexpected = true;
				break;
			}
			tempS += tempC;
			file >> tempC;
		}
		if (unexpected == true)
			continue;

		string T = tempS;
		if (T.size() == 0)
			throw exception("no T name");
		if (contains(T) == false)
			addNode(T);
		tempS.clear();

		file >> tempC;
		while (tempC != '\n' && !file.eof())
		{
			tempS += tempC;
			file >> tempC;
		}
		if (unexpected == true)
			continue;

		int weight = stoi(tempS);
		if (weight < 0)
			throw exception("Negative weight");
		addChannel(S, T, weight);
	}
}

void Network::read(string text)
{
	while (text.size() > 0)
	{
		string tempS;
		char tempC;
		tempC = text[0];
		text.erase(0, 1);
		bool unexpected = false;
		while (tempC != ';')
		{
			if (tempC == '\n' || text.size() == 0)
			{
				unexpected = true;
				break;
			}
			tempS += tempC;
			tempC = text[0];
			text.erase(0, 1);
		}
		if (unexpected == true)
			continue;

		string S = tempS;
		if (S.size() == 0)
			throw exception("no S name");
		if (contains(S) == false)
			addNode(S);
		tempS.clear();

		tempC = text[0];
		text.erase(0, 1);
		while (tempC != ';')
		{
			if (tempC == '\n' || text.size() == 0)
			{
				unexpected = true;
				break;
			}
			tempS += tempC;
			tempC = text[0];
			text.erase(0, 1);
		}
		if (unexpected == true)
			continue;

		string T = tempS;
		if (T.size() == 0)
			throw exception("no T name");
		if (contains(T) == false)
			addNode(T);
		tempS.clear();
		if (text[0] == '\n' || text.size() == 0)
			continue;
		tempC = text[0];
		while (tempC != '\n' && text.size() > 0)
		{
			tempS += tempC;
			text.erase(0, 1);
			tempC = text[0];
		}

		int weight = stoi(tempS);
		if (weight < 0)
			throw exception("Negative weight");
		addChannel(S, T, weight);
	}
}

void Network::addNode(string name)
{
	for (unsigned int i = 0; i < network.GetSize(); ++i)
		if (network[i]->name == name)
			throw exception("ERROR: this node already exists");
	Node* temp = new Node(name);
	network.push_back(temp);
}

void Network::addChannel(unsigned int S, unsigned int T, int capacity)
{
	Node::Channel* temp = new Node::Channel(network[T], capacity);
	network[S]->addChannel(temp);
}

void Network::addChannel(string nameDeparture, string nameDestination, int capacity)
{
	if (capacity < 0)
		throw exception("Negative weight");
	addChannel(stoindex(nameDeparture), stoindex(nameDestination), capacity);
}

void Network::print()
{
	for (unsigned int i = 0; i < network.GetSize(); ++i)
	{
		if (network[i]->name != "")
			cout << network[i]->name;
		else
			cout << i;
		cout << " - ";
		for (unsigned int j = 0; j < network[i]->channels.GetSize(); ++j)
		{
			if (network[i]->channels[j]->T->name != "")
				cout << network[i]->channels[j]->T->name;
			else
				cout << network[i]->channels[j]->T;

			cout << " |" << network[i]->channels[j]->capacity << "| ";
			if (j < network[i]->channels.GetSize() - 1)
				cout << " - ";
			else
				cout << endl;
		}
		cout << endl;
	}
}

bool Network::contains(string name)
{
	for (unsigned int i = 0; i < network.GetSize(); ++i)
		if (network[i]->name == name)
			return true;
	return false;
}

int Network::Algorhytm(string sourceName, string outletName)
{
	return Algorhytm(stoindex(sourceName), stoindex(outletName));
}

int Network::Algorhytm(unsigned int sourceIndex, unsigned int outletIndex)
{
	struct pathway
	{
		List<Node*> path;
		int flow;

		pathway(Node& finalNode)
		{
			this->flow = finalNode.flow;
			Node* current = &finalNode;
			while (current != nullptr)
			{
				path.push_front(current);
				current = current->previous;
			}
		}
	};

	if (sourceIndex >= network.GetSize() || outletIndex >= network.GetSize())
		throw exception("Out of range");

	Node* S = network[sourceIndex];
	Node* T = network[outletIndex];

	List<pathway*> pathways;

	S->flow = numeric_limits<int>::max();

	Node* current = S;
	while (1)
	{
		Node available;
		for (unsigned int i = 0; i < current->channels.GetSize(); ++i)
		{
			if (current->channels[i]->leftover > 0)
				if (current->channels[i]->T->flow == NULL)
				{
					Node::Channel* p = current->channels[i];
					available.addChannel(p);
				}
		}
		if (available.channels.GetSize() == 0)
		{
			if (current == S)
			{
				int total = 0;
				for (unsigned int i = 0; i < pathways.GetSize(); ++i)
				{
					total += pathways[i]->flow;
					for (unsigned int j = 0; j < pathways[i]->path.GetSize(); ++j)
					{
						cout << pathways[i]->path[j]->name;
						if (j != pathways[i]->path.GetSize() - 1)
							cout << " - ";
					}
					cout << " (" << pathways[i]->flow << ")" << endl;
				}
				S->flow = 0;

				for (unsigned int i = 0; i < network.GetSize(); ++i)
					for (unsigned int j = 0; j < network[i]->channels.GetSize(); ++j)
						network[i]->channels[j]->leftover = network[i]->channels[j]->capacity;

				return total;
			}
			else
			{
				Node* temp = current->previous;
				for (unsigned int i = 0; i < temp->channels.GetSize(); ++i)
					if (temp->channels[i]->T == current)
					{
						temp->channels[i]->leftover = 0;
						break;
					}
				current->previous = nullptr;
				current->flow = NULL;
				current = temp;
				continue;
			}
		}
		else
		{
			unsigned int max = 0;
			for (unsigned int i = 0; i < available.channels.GetSize(); ++i)
				if (available.channels[i]->leftover > available.channels[max]->leftover)
					max = i;

			Node* next = available.channels[max]->T;
			next->previous = current;
			if (current->flow > available.channels[max]->leftover)
			{
				next->flow = available.channels[max]->leftover;
				available.channels[max]->leftover = 0;
			}
			else
			{
				next->flow = current->flow;
				available.channels[max]->leftover -= current->flow;
			}

			if (next == T)
			{
				pathways.push_back(new pathway(*next));
				Node* p = next;
				while (p != S)
				{
					for (unsigned int i = 0; i < p->previous->channels.GetSize(); ++i)
						if (p->previous->channels[i]->T == p)
						{
							p->previous->channels[i]->leftover += (p->flow - next->flow);
							if (p != next)
								p->flow = NULL;
							Node* temp = p->previous;
							p->previous = nullptr;
							p = temp;
							break;
						}
				}
				next->flow = NULL;
				current = S;
			}
			else
				current = next;
		}
	}
}

unsigned int Network::stoindex(string input)
{
	unsigned int answer;
	bool success = false;
	for (unsigned int i = 0; i < network.GetSize(); ++i)
	{
		if (network[i]->name == input)
		{
			answer = i;
			success = true;
			break;
		}
	}

	if (success == false)
		throw exception("Couldn't find this dot");
	return answer;
}