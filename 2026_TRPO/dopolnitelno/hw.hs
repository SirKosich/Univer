import System.Environment
import Debug.Trace

list1 :: [Double]
list1 = [1.0000000000000000,
 0.5772156649015329,
 -0.6558780715202538,
 -0.0420026350340952,
 0.1665386113822915,
 -0.0421977345555443,
 -0.0096219715278770,
 0.0072189432466630,
 -0.0011651675918591,
 -0.0002152416741149,
 0.0001280502823882,
 -0.0000201348547807,
 -0.0000012504934821,
 0.0000011330272320,
 -0.0000002056338417,
 0.0000000061160950,
 0.0000000050020075,
 -0.0000000011812746,
 0.0000000001043427,
 0.0000000000077823,
 -0.0000000000036968,
 0.0000000000005100,
 -0.0000000000000206,
 -0.0000000000000054,
 0.0000000000000014,
 0.0000000000000001]


myfunc :: (Double, Double) -> Double
myfunc (a, b) = a + b

x = 3

mysum :: (Double, Double, Double) -> Double
mysum(begin, end, step) | end < begin = 0
                        | otherwise = begin + mysum(begin + step, end, step)

mpow :: (Double, Int) -> Double
mpow(x,n) | n == 0 = 1
          | otherwise = x * mpow(x, n - 1)

mfac :: (Int) -> Integer
mfac (n) | n < 0 = -1
         | n <= 1 = 1
	 | otherwise = fromIntegral(n) * mfac(n-1)


mysin :: (Double) -> Double
mysin (a) = mysininner(a,1)

mysininner :: (Double, Int) -> Double
mysininner (x, n) | n < 0 = -100
                  | n > 100 = 0
		  | otherwise = mpow(-1,n-1) *
		      mpow(x,2*n-1) / fromInteger(mfac(2*n-1)) +
		      mysininner(x, n+1)


mysin2 :: (Double) -> Double
mysin2 (a) = mysininner2(a,1,a)

mysininner2 :: (Double, Int, Double) -> Double
mysininner2 (x, n, inc) | n < 0 = -100
                   | (abs(inc) < 1e-20) && n > 10 = 0
		   | otherwise = trace ("coef: " ++ show inc) $ inc +
		    mysininner2(x, n+1, - inc *
		    x * x / fromIntegral((2*n) * (2*n+1)))  


cycleprint :: Show a => (Double->a,  Double, Double, Int) -> IO()
cycleprint (f, a, b, n)	| n==0 = putStrLn(" "++show b ++ " " ++ show (f(b))++" ")
 	       	     	| n>0 = do
			    putStr (" "++show a ++ " " ++ show (f(a))++" \n")
			    cycleprint(f,a+(b-a)/fromIntegral(n),b, n-1)


mygamma :: (Double, Int) -> Double
mygamma (x,n) | n>26 = 0
	      | otherwise =  (list1 !! (n-1)) * mpow(x,n) +
	                    mygamma(x,n+1)

mg :: (Double) -> Double
mg (x) | x < 1 = 0
       | x > 2 = (x-1) * mg(x-1)
       | otherwise = 1/mygamma(x,1)

main = do
     args <- getArgs
     cycleprint(mg, read(args!!0),read(args!!1),read(args!!2))

  

