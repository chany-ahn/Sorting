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

// Selection Sort

void swapBlocks(std::vector<Block>& blocks, int i, int j) {
	if (i != j) {
		Block tmp = blocks[i];
		blocks[i] = blocks[j];
		blocks[j] = tmp;
	}
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
		swapBlocks(blocks, i, minIdx);
		window.clear();
		displayBlocks(window, blocks);
		window.display();
	}
	
}



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
		selectionSort(window, blocks);
		//window.display();
		
	}
}







