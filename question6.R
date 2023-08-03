```{r }
x = 1:5                       # create value 1,2,...,100
p.x = c(0.1, 0.1, 0.3, 0.3, 0.2)             # probability list
E = sum(x*p.x)                  # expected value
v = sum((x-E)^2)/(length(x) -1) # variance

```

# Q6: 2.
```{r }
x <- sample(1:100, 100, replace = TRUE)  # randomly choose value for rv X
y <- x + 9          # set value for Y
z <- x*(-2)         # set value for z
w <- x*(-2) + 9     # set value for w

mean(x)               # expected value for X
mean(y)               # expected value for y
mean(z)               # expected value for z
mean(w)               # expected value for w

var(x)               # variance for X
var(y)               # variance for w
var(z)               # variance for z
var(w)               # variance for w

```
# Q6:3
Comments for Q6: 
  
  E(Y) = E(X) + 9

E(Z) = -2 * E(X) 

E(W) = -2 * E(X) + 9

V(Y) = V(X)

V(Z) = 2^2 * V(X) = 4 * V(X)

V(W) = 2^2 * V(X) = 4 * V(X)

