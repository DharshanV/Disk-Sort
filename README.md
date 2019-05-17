# Disk-Sort
A sorting program that can sort data in a text file which it cannot hold in memory. Files that may hold 1 GB of data or more. 

## Performance
The sorting I have implemented is blazing fast, and has quailty results.

* Sorting 7.52 MB / 1,000,000 data at 100,000 each chunk
  Average time: 34.036 seconds
  
* Sorting 84.7 MB / 10,000,000 data at 1,000,000 each chunk
  Average time: 364.266 seconds / 6 minutes

* Sorting 943 MB / 100,000,000 data at 1,000,000 each chunk
  Average time: 4589.88 seconds / 76 minutes
  
## Steps
Major functions and there functionality 
* make_chunks(int S,int T)
  - S: size or the amount of data in the text file (ex: 1,000,000)
  - T: size of each chunks
  - Purpose: It is to split one big file into tiny chunks that can fit into memory
* sort_chunks()
  - Purpose: It looks all the tiny chunks and sorts them using merge sort, and write it back to same text file
* merge_chunks()
  - Purpose: It looks all the tiny chunks again, and sorts each into another set of files named "output" followed by index. 
  - Detailed steps: 
    - Read the first element of all files into MinHeap data structure. All the while assigning each data an index of where it came from.
    - Pop form the heap and place into a dynamic array at index (i). And read more data from file of the pop'ed value index.
    - If there no more data in the file at index, then remove that file, since its no longer needed. Then increment the number of exhausted files. 
    - After that write from the dynamic array to the corresponding output index.
    - If the number of exhausted files is the same as number of chunk count, then we are done.
* final_merge()
  - Purpose: It is to look at all the output files and write each one to the final text file that contains all the sorted data.
  
## Improvements
* Use binary mode to read and write files.
* The sorting of all these data could be done with multithreading which can reduce the average time, and I plan to implement it in the future.
