
----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10005.4 | 0.04578 | 5555.44ms | 500299 | 4890 | 2.33049e+06 | 47686.3 | 0.224047 | 0.502003 | 2.16498 | 0.353521 | 0.00249869 | 0.00229708 | 2.95435e-05 | 1(Win) | true |
| Glaze | 5762.05 | 0.249689 | 9151.42ms | 500299 | 640 | 2.7358e+07 | 82804.3 | 0.741874 | 0.871608 | 4.17823 | 0.582038 | 0.00112219 | 0.0013433 | 1.14463e-05 | 2(Loss) | true |
