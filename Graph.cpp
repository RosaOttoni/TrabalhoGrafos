#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>
#include <algorithm>

using namespace std;

/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/

// Constructor
Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node)
{

    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->first_node = this->last_node = nullptr;
    this->number_edges = 0;
}

// Destructor
Graph::~Graph()
{

    Node *next_node = this->first_node;

    while (next_node != nullptr)
    {

        next_node->removeAllEdges();
        Node *aux_node = next_node->getNextNode();
        delete next_node;
        next_node = aux_node;
    }
}

// Getters
int Graph::getOrder()
{

    return this->order;
}
int Graph::getNumberEdges()
{

    return this->number_edges;
}
//Function that verifies if the graph is directed
bool Graph::getDirected()
{

    return this->directed;
}
//Function that verifies if the graph is weighted at the edges
bool Graph::getWeightedEdge()
{

    return this->weighted_edge;
}

//Function that verifies if the graph is weighted at the nodes
bool Graph::getWeightedNode()
{

    return this->weighted_node;
}


Node *Graph::getFirstNode()
{

    return this->first_node;
}

Node *Graph::getLastNode()
{

    return this->last_node;
}

void Graph::setFirstNode(Node* node)
{
    this->first_node = node;
}

void Graph::setLastNode(Node* node)
{
    this->last_node = node;
}

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the graph.
    This allows the correct updating of the numbers of edges in the graph being directed or not.
*/
void Graph::insertNode(int id)
{
    if(this->getFirstNode() == nullptr){
        Node* node = new Node(id);
        this->setFirstNode(node);
        this->setLastNode(node);
    }
    else{
        if(!this->searchNode(id)){
            Node* node = new Node(id);
            this->getLastNode()->setNextNode(node);
            this->setLastNode(node);
        }
        else{
            cerr << "Error: Node " << id << " already exists" << endl;
        }
    }
}

void Graph::insertEdge(int id, int target_id, float weight)
{
    Node *node = this->getNode(id);
    Node *target_node = this->getNode(target_id);

    if(node == nullptr){
        this->insertNode(id);
        node = this->getNode(id);
    }
    if(target_node == nullptr){
        this->insertNode(target_id);
        target_node = this->getNode(target_id);
    }
    if(!node->searchEdge(target_id)){
        if(this->getDirected()){
            node->insertEdge(target_id, weight);
        }
        else{
            node->insertEdge(target_id, weight);
            target_node->insertEdge(id, weight);
        }
    }
    else{
        cerr << "Error: Edge (" << id << "," << target_id << ") already exists" << endl;
    }
}

void Graph::removeNode(int id)
{
    if(this->searchNode(id)){
        Node *node_current = this->getFirstNode();
        Node *node_previous = nullptr;

        while(node_current->getId() != id){
            node_previous = node_current;
            node_current = node_current->getNextNode();
        }
        if(node_previous == nullptr){
            this->setFirstNode(node_current->getNextNode());
        }
        else{
            node_previous->setNextNode(node_current->getNextNode());
        }
        if(node_current->getNextNode() == nullptr){
            this->setLastNode(node_previous);
        }
        node_current->removeAllEdges();
        delete node_current;
    }
    else{
        cerr << "Error: Node " << id << "does not exist" << endl;
    }
}

bool Graph::searchNode(int id)
{
    if(this->first_node != nullptr){
        // Searching for a specific node of a id equal to target id
        for(Node* aux = this->first_node; aux != nullptr; aux = aux->getNextNode()){
            if(aux->getId() == id){
                return true;
            }
        }
    }

    return false;
}

Node *Graph::getNode(int id)
{
    if(this->first_node != nullptr){
        // Searching for a specific node of a id equal to target id
        for(Node* aux = this->first_node; aux != nullptr; aux = aux->getNextNode()){
            if(aux->getId() == id){
                return aux;
            }
        }
    }
    return nullptr;
}
list <int> Graph::directedTransitiveClosureRec(list <int> &closureD, int id){

    closureD.push_back(id);
    for(Node *aux = this->getFirstNode();aux != nullptr; aux = aux->getNextNode()){
        if(aux->getId() == id){
            for(Edge *adj = aux->getFirstEdge(); adj != nullptr; adj = adj->getNextEdge()){
                int targetId = adj->getTargetId();
                if(find(closureD.begin(),closureD.end(),targetId)== closureD.end()){
                    directedTransitiveClosureRec(closureD,targetId);
                }
            }
            break;
        }
    }
    return closureD;
}

list <int> Graph::indirectedTransitiveClosureRec(list <int> &closureI, int id){

    closureI.push_back(id);
    for(Node *aux = this->getFirstNode();aux != nullptr; aux = aux->getNextNode()){
        int nodeId = aux->getId();
        for(Edge *adj = aux->getFirstEdge(); adj != nullptr; adj = adj->getNextEdge()){
            int targetId = adj->getTargetId();
            if((targetId == id) && (find(closureI.begin(),closureI.end(),nodeId)==closureI.end())){
                indirectedTransitiveClosureRec(closureI,nodeId);
                break;
            }
        }
    }
    return closureI;
}

list <int> Graph::directedTransitiveClosure(int id){

    list <int> closureD;
    directedTransitiveClosureRec(closureD,id);
    return closureD;
}

list <int> Graph::indirectedTransitiveClosure(int id){
    list <int> closureI;
    indirectedTransitiveClosureRec(closureI,id);
    return closureI;
}
//Function that prints a set of edges belongs breadth tree

void Graph::breadthFirstSearch(ofstream &output_file){

}



float Graph::floydMarshall(int idSource, int idTarget){

}



float Graph::dijkstra(int idSource, int idTarget){

}

//function that prints a topological sorting
void topologicalSorting(){

}

void breadthFirstSearch(ofstream& output_file){

}
Graph* getVertexInduced(int* listIdNodes){

}

Graph* agmKuskal(){

}
Graph* agmPrim(){

}
