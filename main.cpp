
#include<iostream>
#include<string>
using namespace std;

//            *****************************************Base Class***********************************************

class Media {
    protected:
	   string title, author, type;
	public:
	   Media(string t="", string a="", string tp="Media") {
	   	    title = t; author = a; type = tp;
	   }	
	  virtual void printDetails() { // (virtual for polymorphism)
	   	    cout << "Media: " << title << " by " << author << endl;
	   }
	   string getType() { return type; }
	   
    //       ******************************************Operator overloading********************************************
    
    bool operator==(Media& other) {
    	return (title == other.title && author == other.author);
	}
	
	//       *********************************************Friend function***********************************************
	
	friend void generateReport(Media* collection[], int size);
};

//           **********************************************Derived Classes**********************************************

//           ----------------------------------------Book Class------------------------------------------------------

class Book : public Media {
	    int pages;
	public:
	    Book(string t="", string a="", int p=0) : Media(t,a,"Book") {
	    	pages = p;
		}    
		void printDetails() override {
			cout << "Book: " << title << " by " << author << " (" << pages << " pages)" << endl; 
		}
};

//       -------------------------------------------eBook Class--------------------------------------------------

class eBook : public Media {
        double fileSize;
	public:
	    eBook(string t="", string a="", double f=0) : Media(t,a,"eBook") {
	    	fileSize = f;
		}	
		void printDetails() override {
	    	cout << "eBook: " << title << " by " << author << " [" << fileSize << " MB]" << endl; 
	}
};

//         --------------------------------------------Audiobook Class--------------------------------------------

class Audiobook : public Media {
        double length;
	public:
	    Audiobook(string t="", string a="", double l=0) : Media(t,a,"Audiobook") {
	    	length = l;	    
		}	
		void printDetails() override{
			cout << "Audiobook: " << title << " by " << author << " (" << length << " hrs)" << endl; 	
		}
};

//               *****************************************Friend function for report************************************

void generateReport(Media* collection[], int size) {
	int books=0, ebooks=0, audio=0;
	for(int i=0;i<size;i++) {
		if(collection[i]->getType() == "Book") books++;
		else if(collection[i]->getType() == "eBook") ebooks++;
		else if(collection[i]->getType() == "Audiobook") audio++;
	}
	cout << endl << "\n--- Collection Report ---\n";
	cout << "Total items: " << size << endl;
	cout << "Books: " << books << endl;
	cout << "eBooks: " << ebooks << endl;
	cout << "Audiobooks: " << audio << endl;
}

//               *****************************************Merge two collections***************************************

int merge(Media* c1[], int s1, Media* c2[], int s2, Media* result[]) {
	int k=0;
	for(int i=0;i<s1;i++) result[k++] = c1[i];
	for(int j=0;j<s2;j++) result[k++] = c2[j];
	return k;
}

//               ************************************Function to take input from user***********************************

int inputCollection(Media* collection[], int maxSize, string name) {
	int n;
	cout << "\nHow many items in " << name << "? ";
	cin >> n;
	cin.ignore(); // (to clear buffer after number input)
	
	for(int i=0;i<n;i++) {
		int choice;
		cout << "\nEnter type of item " << i+1 << " (1=Book, 2=eBook, 3=Audiobook): ";
		cin >> choice;
		cin.ignore();
		
		string title, author;
		cout << "Enter Title: ";
		getline(cin, title);
		cout << "Enter Author: ";
		getline(cin, author);
		
		if(choice==1) {
			int pages;
			cout << "Enter number of pages: ";
			cin >> pages; cin.ignore();
			collection[i] = new Book(title, author, pages);
		}
		else if(choice==2) {
			double size;
		    cout << "Enter file size (MB): ";
			cin >> size; cin.ignore();
			collection[i] = new eBook(title, author, size);
		}
		else {
			double hours;
			cout << "Enter length (hours): ";
			cin >> hours; cin.ignore();
			collection[i] = new Audiobook(title, author, hours);
		}
	}
	return n;
}

//                  ***********************************************Main**********************************************

int main() {
	Media* collectionA[10];
	Media* collectionB[10];
	Media* combined[20];
	int sizeA, sizeB, sizeC;
	
	//             *************************************Take input for both collections************************************
	
	sizeA = inputCollection(collectionA,10, "Collection A");
	sizeB = inputCollection(collectionB,10, "Collection B");
	
	//             ******************************************Show collections**********************************************
	
	cout << endl << "\nCollection A:\n";
	for(int i=0;i<sizeA;i++)
	collectionA[i]->printDetails();
	
	cout << endl << "\nCollection B:\n";
	for(int i=0;i<sizeB;i++)
	collectionB[i]->printDetails();
	
	//           *****************************************************Merge*******************************************
	
	sizeC = merge(collectionA, sizeA, collectionB, sizeB, combined);
	
	cout << endl << "\nCombiend Collection:\n";
	for(int i=0;i<sizeC;i++)
	combined[i]->printDetails();
	
	//           *************************************************Compare example**************************************
	
	if(sizeA>0 && sizeB>0) {
		if(*collectionA[0] == *collectionB[0])
		cout << endl << "\nFirst items are same.\n";
		else
		cout << endl << "\nFirst items are different.\n";
	}
	
	//            ****************************************************Report*******************************************
	generateReport(combined, sizeC);
	
	return 0;
}

//     ***************************************************-------------***************************************************





