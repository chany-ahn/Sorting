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
			this->block.setSize(Vector2f(100.0f, this->weight));
		}
		
		void setBlockSize(RenderWindow& window) {
			
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
	window.clear();
	for (int i = 0; i < blocks.size(); i++) {
		blocks[i].displayBlock(window, i);
	}
	window.display();
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
		displayBlocks(window, blocks);
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
				displayBlocks(window, blocks);
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
			displayBlocks(window, blocks);
	}
	recursiveBubbleSort(window, blocks, n-1); // Sort the unsorted subarray
}

// INSERTION SORT

void insertionSort(RenderWindow& window, std::vector<Block>& blocks) {
	int i, j, cur;
	for (i = 1; i < blocks.size(); i++) {
		cur = blocks[i].weight;
		j=i-1;
		while (j >= 0 && cur < blocks[j].weight) {
			blocks[j+1] = blocks[j]; 
			j--;
			displayBlocks(window, blocks);
		}
		blocks[j+1] = blocks[i];
		displayBlocks(window, blocks);
	}
}

// MERGESORT

void merge(RenderWindow& window, std::vector<Block>& blocks, int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	
	std::vector<Block> left(n1);
	std::vector<Block> right(n2);
	
	for(i = 0; i < n1; i++)
		left[i] = blocks[l+i];
	for(j = 0; j < n2; j++)
		right[j] = blocks[m+1+j];
	
	i=0;
	j=0;
	k=l;
	
	while (i < n1 && j < n2) {
		if (left[i].weight <= right[j].weight) {
			blocks[k] = left[i];
			i++;
			displayBlocks(window, blocks);
		}
		else {
			blocks[k] = right[j];
			j++;			
			displayBlocks(window, blocks);
		}
		k++;
	}
	
	while (i < n1) {
		// used to fill in any remainder of the array
		blocks[k] = left[i];
		i++;
		k++;
		displayBlocks(window, blocks);
	}
	
	while (j < n2) {
		// used to fill in any remainder of the array
		blocks[k] = right[j];
		j++;
		k++;
		displayBlocks(window, blocks);
	}
}

void mergeSort(RenderWindow& window, std::vector<Block>& blocks, int l, int r) {
	if (l < r) {
		int m = l + (r-l) / 2;
		mergeSort(window, blocks, l, m);
		mergeSort(window, blocks, m+1, r);
		merge(window, blocks, l, m, r);
	}
	
}

// QUICK SORT

// places pivot at correct index
int partition(RenderWindow& window, std::vector<Block>& blocks, int low, int high) {
	Block pivot = blocks[high];
	int j = low - 1;
	for(int i = low; i <= high-1; i++) {
		if (blocks[i].weight < pivot.weight) {
			j++;
			swapBlocks(&blocks[j], &blocks[i]);
			displayBlocks(window, blocks);
		}
	}
	swapBlocks(&blocks[j+1], &blocks[high]);
	displayBlocks(window, blocks);
	return j+1;
}

void quickSort(RenderWindow& window, std::vector<Block>& blocks, int low, int high) {
	if (low < high) {
		int pivot = partition(window, blocks, low, high); // partitioning index
		
		quickSort(window, blocks, low, pivot-1);
		quickSort(window, blocks, pivot+1, high);
	}
}


int main() {
	// create main window
	RenderWindow window(VideoMode(100, 100), "Sorting");

	// generate the blocks
	int n = 100;
	std::vector<Block> blocks(n);
	
	while(window.isOpen()) {
		generateBlocks(blocks, n);
		Event e;
		while(window.pollEvent(e)) {
			if(e.type == Event::Closed) 
				window.close();
		}
		
		//window.clear();
		// mergeSort(window, blocks, 0, blocks.size()-1);
		quickSort(window, blocks, 0, blocks.size()-1);
		//window.display();
		
	}
}







