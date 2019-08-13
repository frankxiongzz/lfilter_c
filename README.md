# lfilter_c
rewrite python scipy.signal.lfilter in c code

src https://github.com/scipy/scipy/blob/master/scipy/signal/lfilter.c.src

## c code
```
float b[3] = { 0.00013651, 0.00027302, 0.00013651 };
float a[3] = { 1., -1.96668139 , 0.96722743 };
float x[10] = { 2,5,6,7,8,2,3,5,1,2 };
float delay[2] = { 0 ,0 };
float y[1] = {};
for (int i = 0; i < 10; i++)
{
  bb_digital_float_filter(b, a, &x[i], y, delay, 3, 1, 1, 1);
  printf("%f\n", y[0]);
}
```
output:
0.000273
0.001766
0.005665
0.012711
0.023340
0.037021
0.052282
0.068788
0.086627
0.105062


## In python code 
```
from scipy.signal import butter, sosfilt, lfilter
import numpy as np

breath_sos = np.concatenate(butter(2, 0.0075))  #here is the example of b coefficient and a coefficient from python code
breath_zi = np.zeros((1, 2))

testlist = [2,5,6,7,8,2,3,5,1,2]

for i in testlist:
    y_breath, breath_zi = sosfilt(breath_sos, np.array([i]), zi=breath_zi)
    print(y_breath)
```
output:
[0.00027302]
[0.00176554]
[0.00566538]
[0.01271057]
[0.02334023]
[0.03702156]
[0.05228196]
[0.06878833]
[0.08662732]
[0.10506299]
