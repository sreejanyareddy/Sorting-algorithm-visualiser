#include <SDL2/SDL.h>
#include <cstdlib> 
#include <iostream> 
#include <time.h> 
#include <vector>
using namespace std;



SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int height = 900;
int width = 600;
int mx_ele = 100;

vector<int> v_main(mx_ele);

void draw_state(vector<int> &v, int red, int blue){
    for(int i = 0; i < v.size(); i++){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, i, height, i, height-v[i]);
    }
} 

void draw_end(vector<int> &v){
    for(int i = 0; i < mx_ele; i++){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        for(int j = 0; j < i; j++ ){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawLine(renderer, j, height, j, height-v[j]);
        }
        for(int j = i; j < min(i+20, mx_ele); j++){
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderDrawLine(renderer, j, height, j, height-v[j]);
        }
        for(int j = i+20; j < mx_ele; j++){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawLine(renderer, j, height, j, height-v[j]);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(15);
    }
}

void init(){
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 6, 1); 
}

void destroy(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

void insertion_sort(vector<int> v){
    for(int i = 1; i < mx_ele; i++){
        int val = v[i];
        int j = i-1;
        while(val < v[j] && j >= 0){
            v[j+1] = v[j];
            j--;

            // Clear Screen
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // Draw present state
            draw_state(v, 0, 0);

            // Show to window
            SDL_RenderPresent(renderer);
            SDL_Delay(20);
        }

        v[j+1] = val;
        // Clear Screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw present state
        draw_state(v, 0, 0);

        // Show to window
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }

    draw_end(v);
   
}

void selection_sort(vector<int> v){
    for(int i = 0; i < mx_ele; i++){
        
        int min_index = i;
        for(int j = i+1; j < mx_ele; j++){
            if(v[j] < v[min_index]) min_index = j;
        }

        
        swap(v[min_index], v[i]);

        // Clear Screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw present state
        draw_state(v, 0, 0);

        // Show to window
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    draw_end(v);
}

void bubble_sort(vector<int> v){
    for(int i = 0; i < v.size(); i++){
        for(int j = i+1; j < v.size(); j++){
            if(v[j] < v[i]) swap(v[i], v[j]);

            // Clear Screen
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // Draw present state
            draw_state(v, 0, 0);

            // Show to window
            SDL_RenderPresent(renderer);
            SDL_Delay(1);
        }
    }
    draw_end(v);
}


/* MERGE SORT STARTS*/
// Helper for Merge-Sort
void merge(vector<int> &v, int p, int q, int r) {
  
    // Create L ← A[p..q] and M ← A[q+1..r]
    int n1 = q - p + 1;
    int n2 = r - q;

    vector<int> L(n1), M(n2);

    for (int i = 0; i < n1; i++) L[i] = v[p + i];
    for (int j = 0; j < n2; j++) M[j] = v[q + 1 + j];

    // Maintain current index of sub-arrays and main array
    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    // Until we reach either end of either L or M, pick larger among
    // elements L and M and place them in the correct position at A[p..r]
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            v[k] = L[i];
            i++;
        } 
        else {
            v[k] = M[j];
            j++;
        }
        k++;
    }

    // When we run out of elements in either L or M,
    // pick up the remaining elements and put in A[p..r]
    while (i < n1) {
        v[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        v[k] = M[j];
        j++;
        k++;
    }

    // Clear Screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw present state
    draw_state(v, 0, 0);

    // Show to window
    SDL_RenderPresent(renderer);
    SDL_Delay(150);
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(vector<int> &v, int l, int r) {
  if (l < r) {
    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;

    mergeSort(v, l, m);
    mergeSort(v, m + 1, r);

    // Merge the sorted subarrays
    merge(v, l, m, r);
    if(l == 0 && r == v.size()-1) draw_end(v);
  }
}
/* MERGE SORT ENDS*/



// function to rearrange array (find the partition point)
int partition(vector<int> &v, int low, int high) {
    
  // select the rightmost element as pivot
  int pivot = v[high];
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (v[j] <= pivot) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swap(v[i], v[j]);
    }
  }
  
  // swap pivot with the greater element at i
  swap(v[i + 1], v[high]);


    // Clear Screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw present state
    draw_state(v, 0, 0);

    // Show to window
    SDL_RenderPresent(renderer);
    SDL_Delay(150);


  
  // return the partition point
  return (i + 1);
}

void quickSort(vector<int> &v, int low, int high) {
  if (low < high) {
      
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on righ of pivot
    int pi = partition(v, low, high);

    // recursive call on the left of pivot
    quickSort(v, low, pi - 1);

    // recursive call on the right of pivot
    quickSort(v, pi + 1, high);

    if(low == 0 && high == mx_ele-1) draw_end(v);
  }
}



int SDL_main(int argc, char* argv[]){

    cout << "Welcome to the Sorting Visualiser - \n";
    cout << "You can visualise the following sorting types: \n";
    cout << "Bubble Sort (Press 1 and ENTER to run Bubble Sort)\n";
    cout << "Selection Sort (Press 2 and ENTER to run Selection Sort)\n";
    cout << "Insertion Sort (Press 3 and ENTER to run Insertion Sort)\n";
    cout << "Merge Sort (Press 4 and ENTER to run Merge Sort)\n";
    cout << "Quick Sort (Press 5 and ENTER to run Quick Sort)\n";
    cout << "Press -1 and ENTER to exit\n";

    cout << "Enter your option: ";
    int a; cin >> a;
     

   
    while(a != -1 && a < 6 && a > 0){

        srand(time(0));
        for (int i = 0; i < mx_ele; i++) {
            v_main[i] = rand() % (height - 1) + 1;
        }

        init();
        switch (a) {
            case 1:
                bubble_sort(v_main);
                break;
            
            case 2:
                selection_sort(v_main);
                break;

            case 3:
                insertion_sort(v_main);
                break;
                
            case 4:
                mergeSort(v_main, 0, mx_ele-1);
                break;
            
            case 5:
                quickSort(v_main, 0, mx_ele-1);
                break;
            
            default:
                cout << "There is no such option\n";
                break;
        }

        destroy();
        cout << "Press -1 and ENTER to exit\n";
        cout << "If you want to visualise any other Algorithm Press their corresponding number: ";

        cin >> a;
        
    }
    

    cout << "Thank you. Hoping that you've enjoyed the visualisations\n";
   
    
    return 0;
}
