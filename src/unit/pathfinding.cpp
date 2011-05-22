/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include unit.hpp
#include <queue> //Include this for pathfinding?

/* --------------------------------------------------------------
 * Everything related to the unit's pathfinding is defined here.
 * ----------------------------------------------------------- */

class node
{
public:
	float fCost; //Unknown. Might mean "Final cost", as void node::calculateCosts() seems to indicate...
	float gCost; //Unknown.
	float hCost; //Unknown.
	tile* thisTile; //I assume it's a pointer to this tile.
	int thisTile_id; //Pretty much like thisTile, but not a pointer.
	int parent; //Yet to figure out what this is supposed to be.

	node() //The constructor. Initialize an empty node.
	{
		fCost = 0.0f;
		gCost = 0.0f;
		hCost = 0.0f;
		parent = -1;
	}
	~node() {} //The deconstructor.

	//void init() { } //Now obsolete?

	void calculateGCost(vector<node> lon) //Calculates gCost. Whatever that is. I wonder that the lon parameter is...
	{
		if(parent != -1) //Checks it parent is not equal to -1.
		{
			gCost = lon.at(parent).gCost + 10; //It makes this node's gCost 10 more than that of the parent.
			//gCost = lon[parent].gCost + 10; //Alternate method of doing the above. Might crash less or something? Gonna have to experiment.
		}
		else
		{
			gCost = 10; //Hmm. Sets gCost to 10 for some reason.
		}
	}

	void calculateCosts() //Calculates the cost?
	{
		fCost = gCost + hCost; //Uh...Apparently fCost means "Final cost" or something along that line.
	}

	void calculateCostToNode(const node oNode) //Calculates the cost to get to the specified node. Maybe "node *oNode" works better? Also, oNote probably stands for "Other Node"
	{
		hCost = abs(thisTile->wx - oNode.thisTile->wx) + abs(thisTile->wy - oNode.thisTile->wy) * 10.0f; //It takes the WXs of this node's tile and the other node's tile, subtracts them, adds the absolute value of that result to the absolute value of the difference of the WYs of the same two tiles, then finally multiplies the results of that by 10.
		//hCost = (abs(thisTile->wx - oNode.thisTile->wx) + abs(thisTile->wy - oNode.thisTile->wy)) * 10.0f; //This is an alternate version of the above that takes order of operations into account.
	}

	//void calculateCostToNode(node oNode) //Alternate version of the above.
	//{
		//hCost = abs(thisTile->wx - oNode.thisTile->wx) + abs(thisTile->wy - oNode.thisTile->wy) * 10.0f; //It takes the WXs of this node's tile and the other node's tiles, subtracts them, adds the absolute value of that result to the absolute value of the difference of the WYs of the same two tiles, then finally multiplies the results of that by 10.
		////hCost = (abs(thisTile->wx - oNode.thisTile->wx) + abs(thisTile->wy - oNode.thisTile->wy)) * 10.0f; //This is an alternate version of the above that takes order of operations into account.
	//}

	void calculateCostToTile(const tile oTile) //Calculates cost to get to the specified tile. Maybe "tile *oTile" works better? Also, oTile probably stands for "Other Tile"
	{
		hCost = abs(thisTile->wx - oTile.wx) + abs(thisTile->wy - oTile.wy) * 10.0f; //It takes the WXs of this node's tile and the other tile, subtracts them, adds the absolute value of that result to the absolute value of the difference of the WYs of the same two tiles, then finally multiplies the results of that by 10.
		//hCost = (abs(thisTile->wx - oNode.thisTile->wx) + abs(thisTile->wy - oNode.thisTile->wy)) * 10.0f; //This is an alternate version of the above that takes order of operations into account.
	}

	int getNeighbours(node *nbors) //Not sure what this does. //TODO: Check diagonal neighbours.
	{
		int i = 0;
		tile *t = &Map[((thisTile->wx / 32) + ((thisTile->wy / 32)) + ((num_row_objects - 1) * (thisTile->wy / 32 - 1)) - 1) + (num_col_objects * num_row_objects) * (thisTile->layer)];

		if(!t->wall && !t->air && !t->obstruction) //Checks if the specified tile is either a wall, air tile, or obstruction.
		{
			node n;
			//n.init(); //Obsolete.
			//n.parent = this; //Commented out in the original code for some reason.
			n.thisTile = t;
			nbors[i] = n;
			i++;
		}

		t = &Map[((thisTile->wx / 32) + (thisTile->wy / 32)) + ((num_col_objects - 1) * (thisTile->wy / 32 + 1)) + 1 + (num_col_objects * num_row_objects) * (thisTile->layer)];

		if(!t->wall && !t->air && !t->obstruction) //Checks if the specified tile is either a wall, air tile, or obstruction.
		{
			node n;
			//n.init(); //Obsolete.
			//n.parent = this; //Commented out in the original code for some reason.
			n.thisTile = t;
			nbors[i] = n;
			i++;
		}

		t = &Map[((thisTile->wx) / 32) + ((thisTile->wy) / 32) + ((num_row_objects - 1) * ((thisTile->wy / 32))) + 1 + (num_col_objects * num_row_objects) * (thisTile->layer)];

		if(!t->wall && !t->air && !t->obstruction) //Checks if the specified tile is either a wall, air tile, or obstruction.
		{
			node n;
			//n.init(); //Obsolete.
			//n.parent = this; //Commented out in the original code for some reason.
			n.thisTile = t;
			nbors[i] = n;
			i++;
		}

		t = &Map[((thisTile->wx) / 32) + ((thisTile->wy) / 32) + ((num_row_objects - 1) * ((thisTile->wy / 32))) - 1 + (num_col_objects * num_row_objects) * (thisTile->layer)];

		if(!t->wall && !t->air && !t->obstruction) //Checks if the specified tile is either a wall, air tile, or obstruction.
		{
			node n;
			//n.init(); //Obsolete.
			//n.parent = this; //Commented out in the original code for some reason.
			n.thisTile = t;
			nbors[i] = n;
			i++;
		}

		return i;

		//TODO: The parantheses in the first t = blablabla and the other three are arranged slightly different. Might this be causing problems?
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
//That's what the original comment says.
//Personally, I think a plain function would work better here.
class nodeCompare
{
public:
	bool operator() (const node& nodeA, const node& nodeB) const
	{
		return nodeA.fCost > nodeB.fCost;
	}
};

//bool nodeCompater(const node& nodeA, const node& nodeB) const //Alternate version of the above.
//{
//	return nodeA.fCost > nodeB.fCost;
//}

bool bClassUnit::calculate_path() //The main pathfinding code. I think. Either way, it's part of the pathfinding.
{
	if(move == false) //If the unit isn't going anywhere...
	{
		cout << "Error: Can't calculate a path becuase there is no destination!\n";
		out_string << "Error: Can't calculate a path becuase there is no destination!\n";
		return false; //Return to the calling function. False lets it know that no path has been found. The above things log why it failed.
	}

	if(Map[move_destination].wall == true || Map[move_destination].air == true || Map[move_destination].obstruction) //If the destination is a wall, air tile, or an obstruction...
	{
		cout << "Error: Can't move onto the unmovable!\n";
		out_string << "Error: Can't move onto the unmovable!\n";
		return false; //Return to the calling function. False lets it know that no path is found. The above things log why it failed.
	}

	if (Map[move_destination].ramp && Map[move_destination].layer == this->layer) //Once upon a time I knew what this was for.
	{
		move_destination = (num_col_objects * num_row_objects) * (Map[move_destination].up_ramp ? 1 : -1) + move_destination;
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
		// Determine if we have to go up or down or stay. That's what the original comment says.
		if (Map[destination].layer < Map[current].layer) //Is the layer below?
			layerChange = -1;
		else if (Map[destination].layer > Map[current].layer) //Is the layer above?
			layerChange = 1;
		else //Nope, on same layer.
			layerChange = 0;

		bestRamp = -1; //Reset this.

		//Find the ramp that is closest to 'current'. That's what the original comment says.
		for(int i = (num_col_objects * num_row_objects) * (Map[current].layer); i < (num_col_objects * num_row_objects) * (abs(layerChange) + Map[current].layer); i++)
		{
			if(i < 0 || i > Map.size()) //
			{
				//cout << "Problem at line 657\n"; //I commented this out becuase it's sort of obsolete... Replaced with the below.
				cout << "Pathfinding failed at the if i < 0 || i > Map.size() check in the calculate best ramp function.\n";
				out_string << "Pathfinding failed at the if i < 0 || i > Map.size() check in the calculate best ramp function.\n";
				return false;
			}

			//Is this a ramp in the right direction? That's what the original comment says.
			if(Map.at(i).ramp && ((Map.at(i).down_ramp && layerChange < 0) || (Map.at(i).up_ramp && layerChange > 0)))
			{
				if (bestRamp == -1)
				{
					//Make sure that the bestRamp is set. That's what the original comment says.
					bestRamp = i;
					continue;
				}
				//Calculate the distances to the ramps, from our 'current' position. That's what the original comment says.
				float newDistance = 10.0f * (abs(Map[current].wx - Map[i].wx) + abs(Map[current].wy - Map[i].wy));
				float oldDistance = 10.0f * (abs(Map[current].wx - Map[bestRamp].wx) + abs(Map[current].wy - Map[bestRamp].wy));
				
				if (newDistance < oldDistance)
					bestRamp = i; // We have found a closer ramp. That's what the original comment says.
			}
		}
		if (layerChange == 0)
		{
			bestRamp = move_destination;
		}
		//I find the above tidbit of code odd...I'd imagine the layerchange check occuring first. If there was a chekc, then bestramp would be calculated...Hmm...

		if(bestRamp == -1)
		{
			cout << "Error unable to find suitable ramp on this level\n";
			return false;
		}
		//Now we know which ramp is the closest to 'current'. That's what the original comment says.

		destination = bestRamp; // We need to get to the 'bestRamp first'. That's what the original comment says. And I agree with it. Hehehe.

		//Try to find a path clear of obstacles to the destination. That's what the original comment says.
		priority_queue<node, vector<node>, nodeCompare> examineSet; //Nodes to check. That's what the original comment says.
		vector<node> doneSet; //Nodes that are complete. That's what the original comment says.

		node n;// Create a node from the starting tile 'current'. That's what the original comment says.
		//n.init(); //Now obsolete.
		n.thisTile = &Map[current];
		n.calculateCostToTile(Map[destination]); //Destination is stored in 'destination'. That's what the original comment says.
		n.calculateCosts();

		if(current < 0 || current >= Map.size()) //Checks if it failed to assign the tile, or if the tile is out of bounds.
		{
			cerr << "Blargh pathfinding failed. Out of bounds or NULL.\n";
			out_string << "Blargh pathfinding failed. Out of bounds or NULL.\n";
			return false;
		}

		try
		{
			examineSet.push(n); //Add starting node to nodes to be checked. That's what the original comment says. //TODO: This line keeps crashing. Find out why.
			allNodes.push_back(n); //Add this tile to the list of all tiles. That's what the original comment says.
		}
		catch(...)
		{
			cerr << "Blargh pathfinding failed.\n";
			out_string << "Blargh pathfinding failed.\n";
			return false;
		}

		while(!examineSet.empty()) //While we have objects to check. That's what the original comment says.
		{
			n = examineSet.top(); //Get the best next node. That's what the original comment says.
			doneSet.push_back(n); //Add it to the list of good nodes. That's what the original comment says.
			examineSet.pop(); //Remove from list to be checked. That's what the original comment says.

			if(doneSet.at(doneSet.size()-1).thisTile->ID == Map[destination].ID) //Goal? That's what the original comment says.
			{
				goal = true;
				break;
			}

			node near[4]; //List of neighbors, only 4 directions possible. That's what the original comment says.
			int numOfNear = n.getNeighbours(near); //Find those neighbors. That's what the original comment says.
	
			int thisOrd = 0; //The index of the current tile in the allNodes list. That's what the original comment says.
			for(int z = 0;z < allNodes.size();z++) //Need to get a permanent reference to the node, in the allNodes list. That's what the original comment says.
			{
				if(allNodes.at(z).thisTile->ID == n.thisTile->ID)
				{
					thisOrd = z; //This is the index of the parent node. That's what the original comment says.
				}
			}
	
			for(int i = 0, d = 0; i < numOfNear; i++) //Loop through the list. That's what the original comment says.
			{
				near[i].parent = thisOrd; //Set parent node relative to the allNodes list. That's what the original comment says.
	
				for(int z = 0; z < doneSet.size()-1; z++) //Make sure we havent already checked this one. That's what the original comment says.
				{
					if (near[i].thisTile->ID == doneSet.at(z).thisTile->ID)
					{
						d = 1; //If we have set d to 1, or duplicate. That's what the original comment says.
						break;
					}
				}
				if(d == 1)
				{
					//If it is a duplicate, then reset the duplicate indicator and don't store this node. That's what the original comment says.
					d = 0;
					continue;
				}
	
				allNodes.push_back(near[i]); //Add this node to the allNodes list, incase it is a parent. That's what the original comment says.
				
				near[i].calculateCostToTile(Map[destination]); //Calculate cost to get to 'destination from here. That's what the original comment says.
				near[i].calculateGCost(allNodes); // Pass it the allNodes list, so it can get its parent node. That's what the original comment says.
				near[i].calculateCosts(); //Add parent g Cost and cost to goal. That's what the original comment says.

				examineSet.push(near[i]); //Add to list for checking. That's what the original comment says.
			}
		}

		if(goal) //Have we suceeded this run? That's what the original comment says.
		{	
			cout << "Path to ramp found!\n";
			//Extract the movement list from the parent tree. That's what the original comment says.
			int moveOffset = thisMove.size();
			n = doneSet.at(doneSet.size() - 1); // Get the last item in the doneSet
			do 
			{
				thisMove.insert(thisMove.begin() + moveOffset, n.thisTile->ID); //Following the tree of parents, add them to the move_path. That's what the original comment says.
				if(n.parent < 0 || n.parent > allNodes.size())
				{
					cout << "Parent issue at line 766\n";
					cout << "I bet You're on a ramp, or clicked one.\n";
					break;
				}
				else
					n = allNodes.at(n.parent);
			}
			while (n.thisTile->ID != current);
			//Done getting list of moves to get to 'destination'. That's what the original comment says.

			if(thisMove[thisMove.size() - 1] != move_destination)
			{
				if(layerChange == 0)
				{
					cout << "No Path Found\n";
					return false;
				}
				//Set the current location to a different layer than the current one. That's what the original comment says.
				current = destination + ((num_col_objects * num_row_objects) * (layerChange));
				//Re-set the destination as the move_destination. That's what the original comment says.
				destination = move_destination;
			}
		}
		else
		{
			cout << "Couldn't find a path to the destination\n";
			return false;
			//In the future this would step back and say, "Ok, Lets try a different ramp!". That's what the original comment says.
			//As well as store the info that you can get to whatever layer from this ramp...That's what the original comment says.
		}
	}
	while(thisMove[thisMove.size() - 1] != move_destination);

	move_path = thisMove;

	return true; //Succesfully calculated a path. That's what the original comment says.
}
