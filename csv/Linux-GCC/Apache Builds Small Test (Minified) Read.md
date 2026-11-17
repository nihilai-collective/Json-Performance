
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2409.46 | 0.104766 | 836.809ms | 2632 | 160 | 190.588 | 1041.76 | 0.0462174 | 2.18158 | 8.22112 | 1.33093 | 0.000759878 | 2.13716e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 2053.56 | 0.176521 | 855.038ms | 2632 | 160 | 744.853 | 1222.3 | 0.0194268 | 2.54478 | 10.2044 | 1.61854 | 0.00179284 | 6.64894e-05 | 3.08701e-05 | 2(Loss) | true |
| Glaze | 1994.4 | 0.0480204 | 856.999ms | 2632 | 4890 | 1786.1 | 1258.56 | 0.165988 | 2.62013 | 11.0616 | 2.13032 | 0.00045888 | 7.42785e-05 | 3.46529e-05 | 3(Loss) | true |
| simdjson (reflection) | 1752.42 | 0.0776848 | 873.675ms | 2632 | 160 | 198.101 | 1432.34 | 0.0283546 | 2.96819 | 9.53153 | 1.57219 | 0.00226776 | 3.56193e-05 | 2.37462e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1635.19 | 0.140436 | 915.613ms | 2632 | 640 | 2974.21 | 1535.04 | 0.0431399 | 3.17204 | 10.6535 | 1.97986 | 0.00223511 | 0.000114575 | 6.29274e-05 | 5(Loss) | true |
