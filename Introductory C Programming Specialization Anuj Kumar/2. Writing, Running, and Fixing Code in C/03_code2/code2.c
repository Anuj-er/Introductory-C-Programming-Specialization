#include <stdio.h>

int printTriangle(int size) {
  // Start with starCount being 0
  int starCount = 0;
  // Count from 0 (inclusive) to size (exclusive), for each number i that you count
  for(int i = 0; i < size; ++i) {
    // Count from 0 (inclusive) to i (inclusive), for each number j that you count
    for(int j = 0; j <= i; ++j) {
      // Print a "*"
      printf("*");
      // Increment starCount
      starCount += 1;
    }
    // Print a newline ("\n")
    printf("\n");     
  }
  // Your answer is starCount
  return starCount;
}

int main(void) {
  int numStars;
  printf("Here is a triangle with height 4\n");
  numStars = printTriangle(4);
  printf("That triangle had %d total stars\n", numStars);
  // Now print "Here is a triangle with height 7\n"
  printf("Here is a triangle with height 7\n");
  // Then call printTriangle, passing in 7, and assign the result to numStars
  numStars = printTriangle(7);
  // Finally, print "That triangle had %d total stars\n", such that the %d 
  // prints the value of numStars
  printf("That triangle had %d total stars\n", numStars);

  return 0;
}
