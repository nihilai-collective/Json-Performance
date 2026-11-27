
----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1327.2 | 0.0369703 | 1478.49ms | 9739 | 2560 | 17135.8 | 6998.09 | 0.128792 | 3.90489 | 16.7737 | 3.31841 | 0.00390934 | 3.65797e-05 | 1.47602e-05 | 1(Win) | true |
| simdjson (ondemand) | 866.931 | 0.135216 | 1842.43ms | 9739 | 80 | 16788.4 | 10713.5 | 0.324817 | 5.96091 | 28.9526 | 5.51792 | 0.00786272 | 2.69535e-05 | 5.134e-06 | 2(Loss) | true |
