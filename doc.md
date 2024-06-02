1. Introduction
The clustering project implements the Partitioning Around Medoids (PAM) algorithm to cluster a set of data points into a specified number of clusters. Clustering is an unsupervised machine learning technique used to group similar data points together based on their features. This program can be used for various applications such as market segmentation, pattern recognition, and image processing.
Key Features:
 • Data Point Representation: Each data point is represented by its coordinates in n-dimensional space.
 • Clustering: The program assigns each data point to a cluster and recalculates the cluster medoids to minimize the total distance between points and their assigned medoids.
 • Cost Calculation: Computes the total cost (sum of distances) of the clustering to evaluate the clustering quality.
 • Data Reading: Reads data points from a CSV file.
2. System Requirements
To run the clustering project, your system needs to meet the following requirements:
 • Operating System: Windows, macOS, or Linux.
 • Compiler: A C++ compiler supporting C++11 standard or higher (e.g., GCC, Clang, MSVC).
 • C++ Standard Library: Included with most C++ compilers.
 • Doxygen (optional): For generating documentation from source code comments.
