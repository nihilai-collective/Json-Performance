
----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9369.37 | 0.827055 | 751.506ms | 1996 | 640 | 1806.96 | 203.166 | 0.00615299 | 0.649669 | 1.60671 | 0.267034 | 0.000785947 | 4.2272e-05 | 2.34845e-06 | 1(Win) | true |
| Glaze | 3950.4 | 0.29437 | 780.024ms | 1996 | 2560 | 5150.72 | 481.859 | 0.0711256 | 1.38864 | 3.79459 | 0.596193 | 0.000984195 | 5.36229e-05 | 5.67541e-06 | 2(Loss) | true |
