#include "functions.h"
#include "pch.h"

using namespace std;


int genetic(MatrixGraph &graph, double* time, int* resulttab)
{
	
	int numOfVertex = graph.getNumOfVertex();
	vector<vector<int>> population;
	population.reserve(2 * numOfVertex);
	int iterations=10000;
	double mutationProbability=0.4;
	int mutations = 10;
	int crosses=30;
	int sizeOfPopulation=100;
	
	
	vector<int>result;
	int minweight;

	Timer countedTime;
	countedTime.timerStart();

	generatePopulation(population, numOfVertex, sizeOfPopulation);
	int* weights = new int[population.size()];
	
	weights = addWeightAfterCrossing(population, weights, graph, population.size());

	result = population.front();
	minweight = weights[0];

	for (int i = 0; i < iterations; ++i)
	{
		for (int j = 0; j < crosses; ++j)
		{
			cross(population, numOfVertex);
		}
		weights = addWeightAfterCrossing(population, weights, graph, crosses);
		
		for (int j = 0; j < mutations; ++j)
		{
			if (rand() / RAND_MAX < mutationProbability)
			{
				int geneToMutate = rand() % population.size();
				mutation(population[geneToMutate], numOfVertex);
				int weightAfterMutation=changeWeight(weights, graph, population[geneToMutate], geneToMutate);
				if (weightAfterMutation < minweight)
				{
					minweight = weightAfterMutation;
					result.clear();
					result = population[geneToMutate];
				}
			}
		}

		
		qSort(weights, population, 0, population.size() - 1);
		weights = selection(population, weights, sizeOfPopulation);
		
		if (weights[0] < minweight)
		{
			minweight = weights[0];
			result.clear();
			result = population.front();
		}
	}
	countedTime.timerStop();

	*time = countedTime.calculateTime() / (1000000.0);

	cout << "Czas: " << *time << " ms\n";

	resulttab = new int[result.size() + 1];
	for (int i = 0; i < result.size(); ++i)
	{
		resulttab[i] = result[i];
	}
	resulttab[result.size()] = result[0];
	//cout << endl << (double)((minweight- 291.0)/ 291.0)*100.0 << endl;

	return weights[0];
}

void generatePopulation(vector<vector<int>>& population, int numOfVertex,int sizeOfPopulation)
{

	int* numbers = new int[numOfVertex];

	int randNumber;
	vector<int> permutation;

	for (int i = 0; i < sizeOfPopulation; ++i)
	{
		int existnumbers = numOfVertex;
		for (int j = 0; j < numOfVertex; ++j)
			numbers[j] = j;
		while (existnumbers > 0)
		{
			randNumber = rand() % existnumbers;
			permutation.push_back(numbers[randNumber]);
			swap(numbers[randNumber], numbers[existnumbers - 1]);
			existnumbers--;
		}

		/*for (int j = 0; j < permutation.size(); ++j)
		{
			cout << permutation[j] << " ";
		}
		cout << endl;*/
		population.push_back(permutation);
		permutation.clear();
	}

}

void cross(vector<vector<int>>& population, int numOfVertex)
{
	int populationSize = population.size();
	int gene1 = rand() % populationSize;
	int gene2;
	do
	{
		gene2 = rand() % populationSize;
	} while (gene1 == gene2);

	vector<int> subgene;

	bool* used = new bool[numOfVertex];
	for (int i = 0; i < numOfVertex; ++i)
		used[i] = false;
	
	int center = (numOfVertex - 1) / 2;

	for (int i = 0; i <= center; ++i)
	{
		subgene.push_back(population[gene1][i]);
		used[population[gene1][i]] = true;
	}

	for (int i = 0; i < numOfVertex; ++i)
	{
		if(!used[population[gene2][i]]) subgene.push_back(population[gene2][i]);
	}
	//
	//for (int i = 0; i < numOfVertex; i++)
	//{
	//	cout << population[gene1][i] << " ";
	//}
	//cout << endl;
	//for (int i = 0; i < numOfVertex; i++)
	//{
	//	cout << population[gene2][i] << " ";
	//}
	//cout << endl;
	//for (int i = 0; i < numOfVertex; i++)
	//{
	//	cout << subgene[i] << " ";
	//}
	//cout << endl;

	population.push_back(subgene);
	//subgene.clear();


	
	

}

void mutation(vector<int>& gene, int numOfVertex)
{
	int fragment1 = rand() % numOfVertex;
	int fragment2;
	do
	{
		fragment2 = rand() % numOfVertex;
	} while (fragment1 == fragment2);

	//cout << endl << fragment1 << " " << fragment2 << endl;

	swap(gene[fragment1], gene[fragment2]);
}

void showPopulation(vector<vector<int>>& population,int* weights)
{
	int numOfVertex = population[0].size();
	for (int i = 0; i < population.size(); ++i)
	{
		cout << setw(3) << i << ".";
		for (int j = 0; j < numOfVertex; ++j)
		{
			cout<< setw(3)<< population[i][j] << " ";
		}
		cout <<" | "<<weights[i]<< endl;
	}
}

void qSort(int* tab, vector<vector<int>>& pop, int l, int p)
{
	if (l >= p) return;
	int m = partition(tab, pop, l, p);
	qSort(tab, pop, l, m);
	qSort(tab, pop, m + 1, p);
}

int partition(int* tab, vector<vector<int>>& pop, int left, int right)
{
	int pivot = tab[left];
	int l = left; int r = right;
	while (1)
	{
		while (tab[l] < pivot)  ++l;
		while (tab[r] > pivot)  --r;
		if (l < r)
		{
			swap(tab[l], tab[r]);
			swap(pop[l], pop[r]);
			++l;
			--r;
		}
		else
		{
			if (r == right) r--;
			return r;
		}
	}
}

int* addWeightAfterCrossing(vector<vector<int>>& population, int* weights, MatrixGraph& graph, int added)
{
	int populationSize = population.size();
	int* tmptab = new int[populationSize];
	int numofv = graph.getNumOfVertex();

	for (int i = 0; i < populationSize - added; ++i)
	{
		tmptab[i] = weights[i];
	}
	delete[] weights;
	for (int i = populationSize - added; i < populationSize; ++i)
	{
		tmptab[i] = 0;
		for (int j = 0; j < numofv - 1; ++j)
		{
			tmptab[i] += graph.getCost(population[i][j], population[i][j + 1]);
		}
		tmptab[i] += graph.getCost(population[i][numofv - 1], population[i][0]);
		//cout << tmptab[i]<<endl;
	}

	//weights = new int[populationSize];	
	//for (int i = 0; i < populationSize; ++i)
	//{
	//	weights[i] = tmptab[i];
	//}
	
	return tmptab;
}

void getWeights(vector<vector<int>>& population, int *weights, MatrixGraph& graph)
{
	int sizeOfPopulation = population.size();

	int numofv = graph.getNumOfVertex();

	for (int i = 0; i < sizeOfPopulation; ++i)
	{
		weights[i] = 0;
		for (int j = 0; j < numofv-1; ++j)
		{
			weights[i] += graph.getCost(population[i][j], population[i][j + 1]);
		}
		weights[i] += graph.getCost(population[i][numofv - 1], population[i][0]);
	}
}

int changeWeight(int *weights, MatrixGraph& graph, vector<int>& gene, int numOfGene)
{
	weights[numOfGene] = 0;
	int size = gene.size();
	for (int i = 0; i < size-1; ++i)
	{
		weights[numOfGene] += graph.getCost(gene[i], gene[i+1]);
	}
	weights[numOfGene] += graph.getCost(gene[size - 1], gene[0]);
	return weights[numOfGene];
}

int* selection(vector<vector<int>>& population, int* weights, int sizeOfPopulation)
{
	while (population.size() > sizeOfPopulation)
	{
		population.pop_back();
	}

	int* tmpWeights = new int[sizeOfPopulation];

	for (int i = 0; i < sizeOfPopulation; ++i)
		tmpWeights[i] = weights[i];
	delete[] weights;
	return tmpWeights;
}

