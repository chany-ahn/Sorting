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
		Block(int w, int numOfBlocks, int windowSize) {
			this->weight = w;
			this->chosen = 0;
			this->block.setSize(Vector2f(windowSize / numOfBlocks, this->weight));
		}
		
		void setChosen(int x) {
			this->chosen = x;
		}
		
		//display an individual block
		void displayBlock(RenderWindow& window, int x, int scale) {
			this->block.setPosition(scale*x, 0.0f);
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
void generateBlocks(std::vector<Block>& blocks, int n, int w) {
	std::vector<int> nums = generateRandArray(n);
	for (int i = 0; i < n; i++) {
		blocks.push_back(Block(3*nums[i], n, w));
	}
}

// Acts as the update function
void displayBlocks(RenderWindow& window, std::vector<Block>& blocks) {
	int scale = window.getSize().x / blocks.size();
	window.clear();
	for (int i = 0; i < blocks.size(); i++) {
		blocks[i].displayBlock(window, i, scale);
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
		Block cur = blocks[i];
		j=i-1;
		while (j >= 0 && cur.weight < blocks[j].weight) {
			blocks[j+1] = blocks[j]; 
			j--;
			displayBlocks(window, blocks);
		}
		blocks[j+1] = cur;
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
		// begin merging the two partitioned sides into the sorted array.
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

// HEAP SORT

void heapify(RenderWindow& window, std::vector<Block>& blocks, int n, int i) {
	// where n is the size of the heap!
	
	// heapify the subtree
	int largestIdx = i; // input index is the root
	
	// need left and right child for comparisons
	int left = 2*i+1;
	int right = 2*i+2;
	
	
	if (left < n && blocks[left].weight > blocks[largestIdx].weight) {
		largestIdx = left;
	}
	if (right < n && blocks[right].weight > blocks[largestIdx].weight) {
		largestIdx = right;
	}
	
	if (largestIdx != i) {
		// so long as the largest is not the root
		swapBlocks(&blocks[i], &blocks[largestIdx]); // swap the root with the largest child
		displayBlocks(window, blocks);
		heapify(window, blocks, n, largestIdx); // call recursively to form the max heap
	}
}

void heapSort(RenderWindow& window, std::vector<Block>& blocks) {
	// build the heap
	for (int i = (blocks.size()/2)-1; i >= 0; i--) {
		// heapify each root for every subtree
		heapify(window, blocks, blocks.size(), i);
	}		
	
	// extract the heap in the proper order
	for(int i = blocks.size()-1; i > 0; i--) {
		swapBlocks(&blocks[0], &blocks[i]);
		displayBlocks(window, blocks);
		// re-heapify the tree except for the last index where the max index lies
		heapify(window, blocks, i, 0); 
	}
	
}

// to choose the sorting algo of choice
void createStartBoard(RenderWindow& window) {
	int n = 6; // number of sorting algorithms I want to include
	int x = (int) window.getSize().x;
	int y = (int) window.getSize().y;
	
	RectangleShape rect; 
	rect.setSize(Vector2f(x, y/n));
	rect.setOutlineThickness(0.5f);
	rect.setOutlineColor(Color::Black);
	
	// Text!
	sf::Font font;
	if(!(font.loadFromFile("OpenSans-Regular.ttf"))) {
		std::cout << "No font loaded!\n";
	}
	std::vector<Text> texts;
	texts = {
		Text("BubbleSort", font),
		Text("InsertionSort", font),
		Text("SelectionSort", font),
		Text("MergeSort", font),
		Text("QuickSort", font),
		Text("HeapSort", font)
	};
	
	window.clear();
	int j = 0;
	for (int i = 0; i < y; i += y/n) {
		rect.setPosition(0, i+1); // set the position equally spaces across y axis
		window.draw(rect);
		if (j < n) {
			texts[j].setPosition(0, i);
			texts[j].setFillColor(Color::Red);
			window.draw(texts[j]);
			j++;
		}
	}
	window.display();
	
}

void update(RenderWindow& window, std::vector<Block>& blocks, float y) {
	int w = (int) window.getSize().y;
	int i = w / 6;
	if ( y >= 0 && y <= i ) 
		bubbleSort(window, blocks);
	
	else if ( y >= i+1 && y <= 2*i ) 
		insertionSort(window, blocks);
	
	else if ( y >= 2*i+1 && y <= 3*i ) 
		selectionSort(window, blocks);
	
	else if ( y >= 3*i+1 && y <= 4*i ) 
		mergeSort(window, blocks, 0, blocks.size()-1);
	
	else if ( y >= 4*i+1 && y <= 5*i ) 
		quickSort(window, blocks, 0, blocks.size()-1);
	
	else if ( y >= 5*i+1 && y <= 6*i) 
		heapSort(window, blocks);
	
	else 
		return;
	
}

int main() {
	// create main window
	int n; // number of blocks
	int w = 300; // size of window
	float y; // to record y position of the mouse
	RenderWindow window(VideoMode(w, w), "Sorting");
	while(window.isOpen()) {
		std::vector<Block> blocks;
		Event e;
		while(window.pollEvent(e)) {
			if(e.type == Event::Closed) 
				window.close();
			if(e.type == Event::TextEntered) {
				window.close();
			}
		}
		createStartBoard(window);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			y = Mouse::getPosition(window).y;
			if (y >= 0 && y <= window.getSize().y / 2) {
				n = 60;
				generateBlocks(blocks, n, w);
			}
			else {
				n = 100;
				generateBlocks(blocks,n, w);
			}
			window.clear();
			std::cout << y << std::endl;
			update(window, blocks, y);
		}
	}
}
