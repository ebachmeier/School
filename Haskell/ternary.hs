--ternarySearch :: a -> b -> b -> float
ternarySearch f a b tau = if abs(b - a) < tau
  then (a + b)/2
  else do
    let c = a + (b - a)/3
    let d = b - (b - a)/3
    if f(c) < f(d)
      then ternarySearch f c b tau
      else ternarySearch f a d tau

-- Write equation here
--f :: Num float => float
f x = (-)*((x^2) + sin x) 


main = do
y <- ternarySearch f (-1) 1 0.001    -- enter values here
print (y)
print (f y)

