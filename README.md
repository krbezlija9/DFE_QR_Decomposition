=============================
DFE_QR_Decomposition
=============================

QR decomposition of square matrices with full rank using the modified Gram Schmidt algorithm.


Introduction
------------

* Suppose A in an n x n matrix and b and n-dimensional vector
* Our aim is to solve the equation Ax = b
* On efficient way is to decompose the matrix A as a product A = QR, where Q and R are n x n matrices such that R is an upper triangular and Q is an orthonormal matrix  



Usage
-----

* The QR decomposition can be a useful tool for:
  - Linear equations
  - Least squares problems
  - Constrained least squares problems
* Also provides simple formulas for:
  - The pseudo-inverse of a matrix with linearly independent columns
  - The inverse of a non-singular matrix
  - Projection on the range of a matrix with linearly independent columns


How to find Q and R?
--------

* To find Q and R for a matrix A, we used the Modified Gram-Schmidt algorithm
* Since the Q matrix we got need not be orthonormal, we need to orthonormalize it
* That part we skipped, since we only wanted to calculate Q and R using maxeler
