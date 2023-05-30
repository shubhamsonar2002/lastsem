#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

// Function to perform sequential bubble sort
void bubblesort(vector<int> &a){
    int n = a.size();
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(a[j]>a[j+1]){
                swap(a[j],a[j+1]);
            }
        }
    }
}

// Function to perform parallel bubble sort
void parallelbubblesort(vector<int> &a){
    int n = a.size();
    int no_of_threads = omp_get_num_threads(); // Get the number of available threads
    int chunk_size = n/no_of_threads; // Calculate the chunk size for load balancing

    #pragma omp parallel shared(a) num_threads(no_of_threads)
    {
        #pragma omp for schedule(static,chunk_size) // Distribute the work among threads
        for(int i=0;i<n-1;i++){
            for(int j=0;j<n-i-1;j++){
                if(a[j]>a[j+1]){
                    swap(a[j],a[j+1]);
                }
            }
        }
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    omp_set_num_threads(4); // Set the number of threads to be used
    parallelbubblesort(a); // Sort the vector in parallel
    for(int i=0;i<n;i++){
        cout << a[i] << " ";
    }
    return 0;
}
