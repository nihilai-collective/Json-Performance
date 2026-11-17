
----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5728.21 | 0.606804 | 5063.96ms | 9930848 | 80 | 8.05233e+09 | 1.65336e+06 | 0.553765 | 0.432199 | 1(Win) | true |
| Glaze | 3792.68 | 0.250272 | 7762.76ms | 9930228 | 40 | 1.5621e+09 | 2.49697e+06 | 0.211408 | 0.652775 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 245.286 | 3.2235 | 11261.5ms | 10018896 | 30 | 4.73011e+13 | 3.89536e+07 | 4.39679 | 10.0936 | -(Loss) | false |
