
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1326.49 | 0.114311 | 1147.17ms | 5092 | 640 | 11207.9 | 3660.87 | 0.0605157 | 3.92283 | 16.7818 | 2.96131 | 0.00308357 | 2.76168e-05 | 3.06854e-07 | 1(Win) | true |
| simdjson (ondemand) | 1239.17 | 0.0726951 | 1258.86ms | 5092 | 4890 | 39685.6 | 3918.83 | 0.0823224 | 4.15991 | 17.063 | 2.74313 | 0.00514982 | 4.80324e-05 | 1.2731e-05 | 2(Loss) | true |
