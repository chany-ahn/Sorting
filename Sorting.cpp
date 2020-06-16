#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
using namespace sf;

class Block {

	public:
		int weight; // value of the 
		int chosen;
		RectangleShape block;
		
		//Default Constructor for Block object
		Block() {
			this->weight = 0;
			this->chosen = 0;
			this->block.setSize(Vector2f(0.0f, 0.0f));
		}
		
		//Constructor to set weight of the block and to build block
		Block(int w, int n) {
			this->weight = w;
			this->chosen = 0;
			this->block.setSize(Vector2f(n / 800.0f, this->weight));
		}
		
		void setChosen(int x) {
			this->chosen = x;
		}
		
		//display an individual block
		void displayBlock(RenderWindow& window, int x) {
			this->block.setPosition(x, 0.0f);
			if(this->chosen == 1)
				this->block.setFillColor(Color::Red);
			window.draw(this->block);
		}
		
};

// generate an array from 1 - n shuffled around
std::vector<int> generateRandArray(int n) {
	std::vector<int> nums(n);
	for(int i = 1; i <= n; i++) {
		nums[i-1] = i;
	}
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(nums.begin(), nums.end(), gen);
	
	return nums;
}

//generate a block
void generateBlocks(std::vector<Block>& blocks, int n) {
	std::vector<int> nums = generateRandArray(n);
	for (int i = 0; i < blocks.size(); i++) {
		blocks[i] = Block(nums[i], n);
	}
}

// Acts as the update function
void displayBlocks(RenderWindow& window, std::vector<Block>& blocks) {
	for (int i = 0; i < blocks.size(); i++) {
		blocks[i].displayBlock(window, i);
	}
}

/* Sorting Methods */

// SELECTION SORT

void swapBlocks(Block *block1, Block *block2) {
		Block tmp = *block1;
		*block1 = *block2;
		*block2 = tmp;
}


void selectionSort(RenderWindow& window, std::vector<Block>& blocks) {
	for (int i = 0; i < blocks.size(); i++) {
		int curr = blocks[i].weight;
		int minIdx = i;
		for (int j = i+1; j < blocks.size(); j++) {
			if (curr > blocks[j].weight) {
				curr = blocks[j].weight;
				minIdx = j;
			}
		}
		swapBlocks(&blocks[i], &blocks[minIdx]);
		window.clear();
		displayBlocks(window, blocks);
		window.display();
	}
}

// BUBBLE SORT

void bubbleSort(RenderWindow& window, std::vector<Block>& blocks) {
	int i, j;
	bool swapped; // keep track of status of the array
	for (i = 0; i < blocks.size()-1; i++) {
		swapped = false;
		for (j = 0; j < blocks.size()-1-i; j++) {
			if (blocks[j].weight > blocks[j+1].weight) {
				swapBlocks(&blocks[j], &blocks[j+1]);
				window.clear();
				displayBlocks(window, blocks);
				window.display();
				swapped = true;
			}
		}
		if(!swapped) break; // if nothing has been swapped, the blocks are sorted
	}
}

// RECURSIVE BUBBLE SORT

void recursiveBubbleSort(RenderWindow& window, std::vector<Block>& blocks, int n) {
	// Base Case
	if(blocks.size() == 1)
		return;
	for (int i = 0; i < n-1; i++) {
		// sort largest element to the back
		if(blocks[i].weight > blocks[i+1].weight)
			swapBlocks(&blocks[i], &blocks[i+1]);
			window.clear();
			displayBlocks(window, blocks);
			window.display();
	}
	recursiveBubbleSort(window, blocks, n-1); // Sort the unsorted subarray
}

// 

int main() {
	// create main window
	RenderWindow window(VideoMode(800, 800), "Sorting");

	// generate the blocks
	int n = 800;
	std::vector<Block> blocks(n);
	generateBlocks(blocks, n);
	
	while(window.isOpen()) {
		
		Event e;
		while(window.pollEvent(e)) {
			if(e.type == Event::Closed) 
				window.close();
		}
		
		//window.clear();
		recursiveBubbleSort(window, blocks, blocks.size());
		//window.display();
		
	}
}







