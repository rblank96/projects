#include <stdio.h>
#include <stdlib.h>
/* take inputs of number and display a histogram with 16 place holders                                                       
if the input is greater than the max value of the histogram, double the size of                                              
each place holder                                                                                                            
                                                                                                                             
Ryan Blankemeier                                                                                                             
*/

int main(const int argc, char* argv[]){

  //declare variables                                                                                                        

  const int nBins = 30;
  int size = 12;
  int buf[nBins];
  int total = 0;
  int outside = 0;
  int inside = 0;
  //set all the bins to empty                                                                                                
  for (int i = 0; i < nBins; i++){
    buf[i] = 0;
  }
  printf("%d bins of size %d for range [%d,%d]\n",nBins,size,size* nBins - 180,size*nBins - 180);
  float input;

  //if the input is a number                                                                                                 
  while(scanf("%f", &input) == 1){
    //printf("%f%", input);
    // if the input is in range, put it in the correct bin
    if (input <= -120){
      outside+=1;
    }
    if (input > -120 && input <= 0){
      inside+=1;
    }
    total += 1;
  if (input <= size * nBins - 180){
    if (input > 179){
    
    buf[(int)((input+180) / size)-1] +=1;
    }
    else{
    buf[(int)((input+180) / size)] +=1;
    }
    }
    


  // if it is out of range, double the size until it is in range and add it in                                               
  else{
    while(input >= size *nBins){
  int count = 0;
  for (int i = 0; i < nBins/2; i++){
    buf[i] = buf[count] + buf[count+1];
    count = count +2;

  }
  for (int i = nBins/2; i < nBins;i++){
    buf[i] = 0;
  }
  size*=2;
    }
    printf("%d bins of size %d for range [%d,%d)\n",nBins,size,size* nBins - 180,size*nBins - 180); 
  }
  }
  for (int i = 0; i < nBins; i++){
    printf("[%4d,%4d):", i*size- 180, i*size + size - 180);
    for (int j = 0; j < buf[i]/(float)total * 100; j++){
	printf("*");
      }
    printf("%d%%", (int)(((buf[i]/(float)total)*100)+.5));
      printf("\n");
  }
  printf("%d angles in range [-120, 120], %d angles in range [-120,0], %d total angles", outside, inside, total);
}
  
