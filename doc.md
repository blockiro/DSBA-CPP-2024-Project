# **DSBA C++ Data Processing and Clustering Project Documentation**
1. **Introduction** 
> The clustering project implements the Partitioning Around Medoids (PAM) algorithm to cluster a set of data points into a specified number of clusters.
Clustering is an unsupervised machine learning technique used to group similar data points together based on their features. This program can be used for various applications such as market segmentation, pattern recognition, and image processing.
Key Features:
> - Data Point Representation: Each data point is represented by its coordinates in n-dimensional space.
> - Clustering: The program assigns each data point to a cluster and recalculates the cluster medoids to minimize the total distance between points and their assigned medoids.
 > - Cost Calculation: Computes the total cost (sum of distances) of the clustering to evaluate the clustering quality.
 > - Data Reading: Reads data points from a CSV file.

2. **System Requirements**
>To run the clustering project, your system needs to meet the following requirements:
 > - Operating System: Windows, macOS, or Linux.
 > - Compiler: A C++ compiler supporting C++11 standard or higher (e.g., GCC, Clang, MSVC).
 > - C++ Standard Library: Included with most C++ compilers.

3. **User Guide**
>1. **Installation and Setup:**
 > Download the program's source code from the repository or obtain it through another method.
>2. **Compiling the Program:**
 > Open the terminal or command prompt.
 > Navigate to the directory containing the program's source code.
 > Compile the program using a C++ compiler.
 > Ensure that all necessary source code files are in the same directory.
>3. **Running the Program:**
 > Run the compiled executable file of the program in the terminal or command prompt.

>4. **Preparing the Data:**

 > Ensure that your data is in CSV format, where each row represents a data point, and each column represents its attribute.
 > Place the CSV file in the same directory as the program or specify its path when running the program.

>5. **Initiating Clustering:**

 > Launch the program.
 > The program will perform the Partitioning Around Medoids (PAM) clustering algorithm on the provided data.
 > The clustering silhouettes results will be displayed in the files.
