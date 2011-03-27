/* Copright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include unit.hpp
#include <queue> //Include this for pathfinding?

/* --------------------------------------------------------------
 * Everything related to the unit's pathfinding is defined here.
 * ----------------------------------------------------------- */

//A star pathfinding, wraps a tile
class node;
class node
{
public:
	float fCost;
	float gCost;
	float hCost;
	tile* thisTile;
	int parent;
	
	void init()
	{
	}

	void calculateGCost(vector<node> lon)
	{
		if (!(parent == -1))
		{
			gCost = lon.at(parent).gCost + 10;
		}
		else
		{
			gCost = 10;
		}
	}

	void calculateCosts() 
	{
		fCost = gCost + hCost;
	}
	void calculateCostToNode(const node oNode)
	{
		hCost = abs(thisTile->wx - oNode.thisTile->wx) + abs(thisTile->wy - oNode.thisTile->wy) * 10.0f;
	}
	void calculateCostToTile(const tile oTile)
	{
		hCost = abs(thisTile->wx - oTile.wx) + abs(thisTile->wy - oTile.wy) * 10.0f;
	}
	int getNeighbors(node *nbors)
	{
		int i = 0;
		tile *t = &Map[((thisTile->wx / 32) + ((thisTile->wy / 32)) + ((num_row_objects - 1)* (thisTile->wy / 32 - 1)) - 1) + (num_col_objects*num_row_objects)*(thisTile->layer)];
		if (!t->wall && !t->air && !t->obstruction)
		{
			node n;
			n.init();
			//n.parent = this;
			n.thisTile = t;
			nbors[i] = n;
			i++;
		}
		t = &Map[((thisTile->wx / 32) + (thisTile->wy / 32)) + ((num_col_objects - 1)* (thisTile->wy / 32 + 1)) + 1 + (num_col_objects*num_row_objects)*(thisTile->layer)];
		if (!t->wall && !t->air && !t->obstruction)
		{
			node n;
			n.init();
			//n.parent = this;
			n.thisTile = t;
			nbors[i] = n;
			i++;
		}
		t = &Map[((thisTile->wx) / 32) + ((thisTile->wy) / 32) + ((num_row_objects - 1)* ((thisTile->wy / 32))) + 1 + (num_col_objects*num_row_objects)*(thisTile->layer)];
		if (!t->wall && !t->air && !t->obstruction)
		{
			node n;
			n.init();
			//n.parent = this;
			n.thisTile = t;
			nbors[i] = n;
			i++;
		}
		t = &Map[((thisTile->wx) / 32) + ((thisTile->wy) / 32) + ((num_row_objects - 1)* ((thisTile->wy / 32))) - 1 + (num_col_objects*num_row_objects)*(thisTile->layer)];
		if (!t->wall && !t->air && !t->obstruction)
		{
			node n;
			n.init();
			//n.parent = this;
			n.thisTile = t;
			nbors[i] = n;
			i++;
		}

		return i;
	}

	node() //The constructor. Initialize an empty node.
	{
		fCost = 0.0f;
		gCost = 0.0f;
		hCost = 0.0f;
		parent = -1;
	}
	~node() //The deconstructor.
	{
	}
	node(const node &cNode) //The copy constructor.
	{
		fCost = cNode.fCost;
		gCost = cNode.gCost;
		hCost = cNode.hCost;
		parent = cNode.parent;
		thisTile = cNode.thisTile;
	}
};
//Compares 2 nodes for best one
class nodeCompare
{
public:
	bool operator() (const node& nodeA, const node& nodeB) const
	{
		return nodeA.fCost > nodeB.fCost;
	}
};

bool bClassUnit::calculate_path()
{	
	if(move == false) //If the unit isn't going anywhere...
	{
		cout << "Error: Can't calculate a path becuase there is no destination!\n";
		out_string << "Error: Can't calculate a path becuase there is no destination!\n";
		return false; //Return to the calling function. False lets it know that no path has been found. The above things log why it failed.
	}
	if(Map[move_destination].wall == true || Map[move_destination].obstruction) //If the destination is a wall...
	{
		cout << "Error: Can't move on a wall!\n";
		out_string << "Error: Can't move on a wall!\n";
		return false; //Return to the calling function. False lets it know that no path is found. The above things log why it failed.
	}
	if (Map[move_destination].ramp && Map[move_destination].layer == this->layer)
	{
		move_destination = (num_col_objects*num_row_objects)*(Map[move_destination].up_ramp ? 1 : -1) + move_destination;
	}
	
	vector<node> allNodes;
	vector<int> thisMove;

	int destination = move_destination;	
	int start = (((((wx) / 32) + ((wy) / 32)) + ((num_col_objects - 1)* ((wy / 32)) ) )) + (num_col_objects*num_row_objects)*(this->layer);
	int current = start;
	bool goal = false;
	int bestRamp = -1;
	int layerChange = 0;

	do
	{

		// Determine if we have to go up or down or stay
		if (Map[destination].layer < Map[current].layer)
			layerChange = -1;
		else if (Map[destination].layer > Map[current].layer)
			layerChange = 1;
		else
			layerChange = 0;
	
		bestRamp = -1;
		// Find the ramp that is closes to 'current'
		for (int i = (num_col_objects*num_row_objects)*(Map[current].layer); i < (num_col_objects*num_row_objects)*(abs(layerChange)+Map[current].layer); i++)
		{
			if (i < 0 || i > Map.size())
			{
				cout << "Problem at line 657\n";
				return false;
			}
			// Is this a ramp in the right direction?
			if (Map.at(i).ramp && ((Map.at(i).down_ramp && layerChange < 0) || (Map.at(i).up_ramp && layerChange > 0)))
			{
				if (bestRamp == -1)
				{
					// Make sure that the bestRamp is set
					bestRamp = i;
					continue;
				}
				// Calculate the distances to the ramps, from our 'current' position
				float newDistance = 10.0f * (abs(Map[current].wx - Map[i].wx) + abs(Map[current].wy - Map[i].wy));
				float oldDistance = 10.0f * (abs(Map[current].wx - Map[bestRamp].wx) + abs(Map[current].wy - Map[bestRamp].wy));
				
				if (newDistance < oldDistance)
					bestRamp = i; // We have found a closer ramp
			}
		}
		if (layerChange == 0)
		{
			bestRamp = move_destination;
		}
		if (bestRamp == -1)
		{
			cout << "Error unable to find suitable ramp on this level\n";
			return false;
		}
		//Now we know which ramp is the closest to 'current'

		destination = bestRamp; // We need to get to the 'bestRamp first'		

		// Try to find a path clear of obstacles to the destination.
		priority_queue<node, vector<node>, nodeCompare> examineSet; // Nodes to check
		vector<node> doneSet; // Nodes that are complete
				
		node n; // Create a node from the starting tile 'current'
		n.init();
		n.thisTile = &Map[current];
		n.calculateCostToTile(Map[destination]); // Destination is stored in 'destination'
		n.calculateCosts();

		examineSet.push(n); // Add starting node to nodes to be checked
		allNodes.push_back(n); // Add this tile to the list of all tiles

		while (!examineSet.empty()) // While we have objects to check
		{
			n = examineSet.top(); // Get the best next node
			doneSet.push_back(n); // Add it to the list of good nodes
			examineSet.pop(); // Remove from list to be checked

			if (doneSet.at(doneSet.size()-1).thisTile->ID == Map[destination].ID) //Goal?
			{
				goal = true;
				break;
			}

			node near[4]; // List of neighbors, only 4 directions possible
			int numOfNear = n.getNeighbors(near); // Find those neighbors
	
			int thisOrd = 0; // The index of the current tile in the allNodes list
			for (int z = 0;z < allNodes.size();z++) // Need to get a permanent reference to the node, in the allNodes list
			{
				if (allNodes.at(z).thisTile->ID == n.thisTile->ID)
				{
					thisOrd = z; // This is the index of the parent node
				}
			}
	
			for (int i = 0,d = 0; i < numOfNear; i++) // Loop through the list
			{
				near[i].parent = thisOrd; // Set parent node relative to the allNodes list
	
				for (int z = 0;z < doneSet.size()-1;z++) // Make sure we havent already checked this one
				{
					if (near[i].thisTile->ID == doneSet.at(z).thisTile->ID)
					{
						d = 1; // If we have set d to 1, or duplicate
						break;
					}
				}
				if (d == 1)
				{
				// If it is a duplicate, then reset the duplicate indicator and dont store this node
					d = 0;
					continue;
				}
	
				allNodes.push_back(near[i]); // Add this node to the allNodes list, incase it is a parent
				
				near[i].calculateCostToTile(Map[destination]); //Calculate cost to get to 'destination from here
				near[i].calculateGCost(allNodes); // Pass it the allNodes list, so it can get its parent node
				near[i].calculateCosts(); //Add parent g Cost and cost to goal

				examineSet.push(near[i]); //Add to list for checking
			}
		}

		if (goal) // Have we suceeded this run?
		{	
			cout << "Path to ramp found!\n";
			// Extract the movement list from the parent tree
			int moveOffset = thisMove.size();
			n = doneSet.at(doneSet.size()-1); // Get the last item in the doneSet
			do 
			{
				thisMove.insert(thisMove.begin() + moveOffset,n.thisTile->ID); // Following the tree of parents, add them to the move_path
				if (n.parent < 0 || n.parent > allNodes.size())
				{
					cout << "Parent issue at line 766\n";
					cout << "I bet You're on a ramp, or clicked one.\n";
					break;
				}
				else
					n = allNodes.at(n.parent);
			}
			while (n.thisTile->ID != current);
			// Done getting list of moves to get to 'destination'

			if (thisMove[thisMove.size()-1] != move_destination)
			{
				if (layerChange == 0)
				{
					cout << "No Path Found\n";
					return false;
				}
				// Set the current location to a different layer than the current one
				current = destination + ((num_col_objects*num_row_objects)*(layerChange));
				// Re-set the destination as the move_destination
				destination = move_destination;
			}
		}
		else
		{
			cout << "Couldn't find a path to the destination\n";
			return false;
			// In the future this would step back and say, "Ok, Lets try a different ramp!"
			// As well as store the info that you can get to whatever layer from this ramp...
		}

	}
	while (thisMove[thisMove.size()-1] != move_destination);

	move_path = thisMove;

	return true; //Succesfully calculated a path.
}
