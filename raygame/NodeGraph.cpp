#include "NodeGraph.h"
#include "Edge.h"
#include "Node.h"
#include <raylib.h>
#include <deque>

std::deque<NodeGraph::Node*> NodeGraph::findPath(Node* start, Node* end)
{
	//This helps use start and end without errors
	Node* start = start;
	Node* goal = end;

	if (!start || !goal)
		return;

	start->color = ColorToInt(GREEN);
	start->visited = true;

	Node* currentNode = start;

	std::deque<Node*> queue;
	queue.push_front(start);

	while (!queue.empty())
	{
		currentNode = queue[0];
		queue.pop_front();

		if (currentNode == goal)
		{
			currentNode->color = ColorToInt(YELLOW);
			return;
		}

		for (int i = 0; i < currentNode->edges.size(); i++)
		{
			Node* currentEdgeEnd = nullptr;

			if (currentNode == currentNode->edges[i]->connectedNode2)
				currentEdgeEnd = currentNode->edges[i]->connectedNode1;

			else
				currentEdgeEnd = currentNode->edges[i]->connectedNode2;

			if (!currentEdgeEnd->visited)
			{
				currentEdgeEnd->color = ColorToInt(RED);
				currentEdgeEnd->visited = true;
				queue.push_front(currentEdgeEnd);
			}

		}
	}
}

void NodeGraph::drawGraph(Node* start)
{
	std::deque<Node*>* drawnList = new std::deque<Node*>();
	drawConnectedNodes(start, drawnList);
	delete drawnList;
}

void NodeGraph::drawNode(Node* node, int color)
{
	static char buffer[10];
	sprintf_s(buffer, "%.0f", node->gScore);

	//Draw the circle for the outline
	DrawCircle((int)node->position.x, (int)node->position.y, 16, GetColor(color));
	//Draw the inner circle
	DrawCircle((int)node->position.x, (int)node->position.y, 14, BLACK);
	//Draw the text
	DrawText(buffer, (int)node->position.x, (int)node->position.y, 24, RAYWHITE);
}

void NodeGraph::drawConnectedNodes(Node* node, std::deque<Node*>* drawnList)
{
	//drawNode(node);
	drawnList->push_back(node);

	//For each Edge in this node's connections
	for (Edge e : node->connections) {
		//Draw the Edge
		DrawLine((int)node->position.x, (int)node->position.y, (int)e.target->position.x, (int)e.target->position.y, WHITE);
		//Draw the cost
		MathLibrary::Vector2 costPos = { (node->position.x + e.target->position.x) / 2, (node->position.y + e.target->position.y) / 2 };
		static char buffer[10];
		sprintf_s(buffer, "%.0f", e.cost);
		DrawText(buffer, (int)costPos.x, (int)costPos.y, 16, RAYWHITE);
		//Draw the target node
		if (std::find(drawnList->begin(), drawnList->end(), e.target) == drawnList->end()) {
			drawConnectedNodes(e.target, drawnList);
		}
	}
}
