#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

struct Node {
    int x, y;

};

const int NUM_NODES=5;
const int POPULATION_SIZE=400;
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

     /*void startNode (int startNode) {
        fill (visited.begin(), visited.end(), false);
        visited[startNode]=true;
        genes[0]= startNode;
        fitness = 0;
    }*/

    /*void createRandomRoute (){
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
    }*/

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
        //cout<<"mutation rate is"<<MUTATION_RATE<<endl;
        //cout<<"rand number is"<<randnum<<endl;
        if (randnum<MUTATION_RATE){
            int k = genes [index_city1]; //k is used to keep the first random city
            //cout<<"index city 1 is"<<index_city1<<"\t"<<"index city 2 is"<<index_city2;
            genes[index_city1] = genes[index_city2];
            genes[index_city2] = k; //code lines 85 and 86 are used to exchange cities in one genes
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
        //cout<<"index_cut1 = "<<index_cut1<<"\t"<<"index_cut2 = "<<index_cut2<<endl;
        for (int i=index_cut1; i<=index_cut2; i++){
            offspring1.genes[i] = genes[i];
            //cout<<"offspring.genes["<<i<<"] = "<<offspring1.genes[i]<<"\t";
        }
        vector<int> intermediaryGene(NUM_NODES);
        vector<bool> canbeselected(NUM_NODES, true);
        int l=(NUM_NODES-(index_cut2-index_cut1+2));
        vector<int> indexes(l);// the indexes that have to be added to offspring1
        int t=1;
        for(int i=index_cut2+1; i<NUM_NODES; i++){
            intermediaryGene[t]=other.genes[i];
            //cout<<"intermediaryGene["<<t<<"] = "<<intermediaryGene[t]<<"\t";
            t++;
        }
        for(int i=1; i<index_cut2+1; i++){
            intermediaryGene[t]=other.genes[i];
            //cout<<"intermediaryGene["<<t<<"] = "<<intermediaryGene[t]<<"\t";
            t++;
        }
       
       for(int i=index_cut1; i<=index_cut2; i++){
            for(int j=1; j<NUM_NODES; j++){
                if(offspring1.genes[i]==intermediaryGene[j]){
                    canbeselected[j]=false;
                    //cout<<"canbeselected["<<j<<"] = "<<canbeselected[j]<<endl;
                }
            }
       }
       
       int y=0;
       for(int i=1; i<NUM_NODES; i++){
        if(canbeselected[i]==true){
            indexes[y]=intermediaryGene[i];
            //cout<<"intermediary"<<i<<"="<<intermediaryGene[i]<<"\t";
            //cout<<"indexes["<<y<<"]="<<indexes[y]<<"\t";
            y++;
        }
       }
       int k=0;
       
        
       for(int i=index_cut2+1; i<NUM_NODES; i++){
                offspring1.genes[i] = indexes[k];
                k++;
                //cout<<"offspring1.genes["<<i<<"] = "<<offspring1.genes[i]<<"\t";
       }

       for(int i=1; i<index_cut1; i++){
                offspring1.genes[i] = indexes[k];
                k++;
                //cout<<"the begin of offspring1.genes["<<i<<"] = "<<offspring1.genes[i]<<"\t";
       }

        /*for(int i=0; i<NUM_NODES; i++){
            cout<<"offpring1.genes["<<i<<"]= "<<offspring1.genes[i]<<"\t";
        }
        cout<<endl;*/
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
                //cout<<" x.fitness is= "<<x.fitness<<"\t";
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
        cout<<"generation 1"<<" best solution fitness = "<<maxIndividual.fitness<<endl;
        for (int generation=0; generation<GENERATIONS -1; generation++){
            population.generateNewGeneration();
            Individual best = population.selectBest();
            //cout<<"generation"<<generation+1<<best.fitness<<endl;
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
    
    /*ifstream myfile ("geneticTSP.txt");
    string mystring;
    if ( myfile.is_open() ) { // always check whether the file is open
    myfile >> mystring; // pipe file's content into stream
    cout << mystring; // pipe stream's content to standard output
    }*/
    srand(time(0));
    Genetic ga;
    ga.run();
    
    
    
    /*Individual object1(NUM_NODES);
    Individual object2(NUM_NODES);
    
    /*for (int i=0; i<NUM_NODES; i++){
        //cout<<object1.nodes[i].x;
        //cout<<object1.nodes[i].y<<endl;
        for(int j=0; j<NUM_NODES; j++){
            cout<<object1.distances[i][j]<<"\t";
        }
        cout<<endl;
    }
    //cout<<"before"<<object1.genes[0]<<endl;
    object1.startNode(1);
    object2.startNode(1);
    //cout<<"after"<<object1.genes[0]<<endl;
    object1.createRandomRoute();
    object2.createRandomRoute();

    //cout<<"before mutation"<<endl;

  for (int i=0; i<NUM_NODES; i++){
    cout<<object1.genes[i];
    }
    cout<<endl;
    for (int i=0; i<NUM_NODES; i++){
    cout<<object2.genes[i];
    }


    object1.crossover(object2);
    object1.mutate();
    //cout<<"fitness is"<<object1.fitness<<endl;
  //cout<<"after mutation"<<endl;

  for (int i=0; i<NUM_NODES; i++){
    //cout<<object1.genes[i];
    }


 
    
    Population object3 (NUM_NODES);
    object3.selectBest();
    /*cout<<endl;
    cout<<"test 1"<<endl;
    cout<<"fitness"<<object3.individuals[0].fitness<<endl;
    for(int i=0; i<POPULATION_SIZE; i++){
        cout<<"the fitness of the "<<i<<"th individual is"<<object3.individuals[i].fitness;
    }*/

    return 0;
}