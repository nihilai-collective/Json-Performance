
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2236.89 | 0.0714403 | 6825.19ms | 264040 | 320 | 2.06961e+06 | 112571 | 0.082455 | 2.27038 | 8.95182 | 1.63284 | 0.00578468 | 1.92442e-05 | 1.49125e-06 | 1(Win) | true |
| simdjson (ondemand) | 1818.99 | 0.0888541 | 8235.77ms | 264040 | 640 | 9.68313e+06 | 138433 | 0.00419331 | 2.7751 | 9.84533 | 1.51625 | 0.0122121 | 1.42497e-05 | 4.88207e-06 | 2(Loss) | true |
