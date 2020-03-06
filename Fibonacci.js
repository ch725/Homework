function Fibonacci_of (n , ac1 = 0 , ac2 = 1) {
  if( n <= 1 ) {return ac2};
  return Fibonacci_of (n - 1, ac2, ac1 + ac2);
}

for(let i=1; i<=200; i++){
    console.log('Fibonacci_of(%d) == %d',i,Fibonacci_of(i));
}