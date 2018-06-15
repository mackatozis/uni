<html>
   <head>
      <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
   </head>

   <body>
	<div>
	<p>This program is testing the traversal through different screens. The program is written in C programming language.</p>
	<p align="middle"><a href="http://tinypic.com?ref=344fvvr" target="_blank"><img src="http://i50.tinypic.com/344fvvr.jpg" border="0" alt="Image and video hosting by TinyPic" align="middle" width="400" height="273""></a></p>
	<h3>Input</h3>
	<p align="justify">The first line of test case will contain two integers: N(N<= 100) and R representing respectively the number of screens and the connection between screens. Then R lines will follow each containing three integers: C1, C2 and P. C1 and C2 are the screen numbers and P (P>1) is the limit on the minimum server response time to navigate to the screen. Last line of the input should be the source and the destination screen. Screen numbers are positive integers ranging from 1 to N.
	</p>
	<h3>Output</h3>
	<p>Output the shortest time to traverse from source to destination and back without repeating any screen.
</p>
	<p></p>
	<h3>To compile:</h3>
	<p><code>gcc nodes.c -o nodes</code></p>
	<h3>To run:</h3>
	<p><code>./nodes</code></p>
	<h3>Sample Input:</h3>
	<p><code>7 10</code></p>
	<p><code>1 2 30</code></p>
	<p><code>1 3 20</code></p>
	<p><code>1 4 10</code></p>
	<p><code>2 4 25</code></p>
	<p><code>2 5 60</code></p>
	<p><code>3 6 70</code></p>
	<p><code>4 7 35</code></p>
	<p><code>4 6 20</code></p>
	<p><code>5 7 10</code></p>
	<p><code>6 7 15</code></p>
	<h3>Sample Output:</h3>
	<p><code>145</code></p>
	</div>
   </body>
</html>
