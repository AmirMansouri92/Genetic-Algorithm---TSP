#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

struct Node {
    int x, y;

};

const int NUM_NODES=10;
const int POPULATION_SIZE=100;
const int GENERATIONS=100;
const int STARTNODE =1;
const double MUTATION_RATE=0.2;

double calculateDistance (Node& a, Node& b){
    return sqrt(pow (a.x-b.x, 2)+pow (a.y-b.y, 2));
};
class Individual {
    public:
    vector <int> genes;
    vector <bool> visited;
    double fitness;
    vector <Node> nodes = generateNodes();  
    vector <vector <double>> distances = calculateDistances(); 

    Individual (int NUM_NODES): fitness(0.0) {
        genes.resize(NUM_NODES);
        visited.resize (NUM_NODES, false);
        fill (visited.begin(), visited.end(), false);
        visited[STARTNODE]=true;
        genes[0]= STARTNODE;
        fitness = 0;
        int nextnode;
        int nbselected=1; //the number of selected nodes at the beginning which is 1 (we have already chosen the first node of the route)
        while (nbselected<NUM_NODES){
            nextnode = (rand()%NUM_NODES);
            if(visited [nextnode]!=true){
                genes[nbselected] = nextnode;
                visited[nextnode]=true;
                nbselected++;
            }
        }

        calculateFitness();
    }

    vector <Node> generateNodes (){
        vector <Node> nodes (NUM_NODES);
        for (int i=0; i<NUM_NODES; i++){
            nodes[i]={rand ()%100, rand ()%100};
        }
        return nodes;
    };

    vector<vector<double>> calculateDistances(){
        vector<vector<double>> distances(NUM_NODES, vector<double>(NUM_NODES, 0.0));
        for (int i=0; i <NUM_NODES; i++){
            for (int j=0; j<NUM_NODES; j++){
              distances[i][j]=calculateDistance(nodes[i], nodes[j]);
            } 
        }
        return distances; 
    }        

    double calculateFitness (){
        fitness = 0.0;
        for (int i=0; i< genes.size()-1; i++){
            fitness += distances[genes[i]][genes[i+1]];
        }
        fitness+= distances [genes[NUM_NODES-1]][genes[0]];
        return fitness;
    }

    void mutate(){
        int index_city1, index_city2;
        index_city1=index_city2=10;
        while(index_city1 == index_city2){
            index_city1 = (rand ()% ((NUM_NODES)-1)+1); //the first city to exchange
            index_city2 = (rand ()% ((NUM_NODES)-1)+1); //the second random city to exchange
        }

        double randnum=rand()/(double)RAND_MAX;
        if (randnum<MUTATION_RATE){
            int k = genes [index_city1]; 
            genes[index_city1] = genes[index_city2];
            genes[index_city2] = k; //code lines 88 and 89 are used to exchange cities in one gene
            calculateFitness();
        }
    }

    Individual crossover(const Individual& other) const {
        Individual offspring1 (NUM_NODES);
        int index_cut1, index_cut2;
        index_cut1=1;
        index_cut2=1;
        while(index_cut1==index_cut2 || (index_cut1-index_cut2)==(NUM_NODES-2) || (index_cut2-index_cut1)==(NUM_NODES-2) || (index_cut1>index_cut2)){
            index_cut1=(rand()%(NUM_NODES-1))+1;
            index_cut2=(rand()%(NUM_NODES-1))+1;
        }
        offspring1.genes[0] = genes[0]; // the beginning city doesn't change
        for (int i=index_cut1; i<=index_cut2; i++){
            offspring1.genes[i] = genes[i];
        }
        vector<int> intermediaryGene(NUM_NODES);
        vector<bool> canbeselected(NUM_NODES, true);
        int l=(NUM_NODES-(index_cut2-index_cut1+2));
        vector<int> indexes(l);// the indexes that have to be added to offspring1
        int t=1;
        for(int i=index_cut2+1; i<NUM_NODES; i++){
            intermediaryGene[t]=other.genes[i];
            t++;
        }
        for(int i=1; i<index_cut2+1; i++){
            intermediaryGene[t]=other.genes[i];
            t++;
        }
       
       for(int i=index_cut1; i<=index_cut2; i++){
            for(int j=1; j<NUM_NODES; j++){
                if(offspring1.genes[i]==intermediaryGene[j]){
                    canbeselected[j]=false;
                }
            }
       }
       
       int y=0;
       for(int i=1; i<NUM_NODES; i++){
        if(canbeselected[i]==true){
            indexes[y]=intermediaryGene[i];
            y++;
        }
       }
       int k=0;
       
        
       for(int i=index_cut2+1; i<NUM_NODES; i++){
                offspring1.genes[i] = indexes[k];
                k++;
       }

       for(int i=1; i<index_cut1; i++){
                offspring1.genes[i] = indexes[k];
                k++;
       }

        
        return offspring1;

    }
        
};

class Population {
    public:
    vector<Individual> individuals; 

    Population(int NUM_NODES){
        for(int i=0; i<POPULATION_SIZE; i++){
            individuals.push_back(Individual(NUM_NODES));
        }
    }


    Individual selectBest(){
        Individual bestIndividual=individuals[0];
        for (const auto& x : individuals){
            if(x.fitness<bestIndividual.fitness){
                bestIndividual=x;
            }
        }
        return bestIndividual;
    }

    void generateNewGeneration (){
        vector<Individual> newPopulation;
        for(int i=0; i<POPULATION_SIZE; i++){
            Individual parent1=selectBest();
            Individual parent2=individuals[rand()%individuals.size()];
            Individual offspring=parent1.crossover(parent2);
            offspring.mutate();
            offspring.calculateFitness();
            newPopulation.push_back(offspring);
        }
        individuals=newPopulation;
    }
    
};

class Genetic{
    public:
    void run(){
        Population population(NUM_NODES);
        int generation=0;
        for(auto& x: population.individuals){
            x.calculateFitness();
        }
        population.generateNewGeneration();
        Individual maxIndividual = population.selectBest();

        for (int generation=0; generation<GENERATIONS -1; generation++){
            population.generateNewGeneration();
            Individual best = population.selectBest();
            if(best.fitness<maxIndividual.fitness){
                maxIndividual=best;
            }
        }
        cout<<"best individual fitness is = "<<maxIndividual.fitness<<endl;
        cout<<"the best found route is = "<<endl;
        for(int i=0; i<NUM_NODES; i++){
            cout<<maxIndividual.genes[i]<<" ";
        }

    }
};

int main(){
    
    srand(time(0));
    Genetic ga;
    ga.run();
    return 0;
}