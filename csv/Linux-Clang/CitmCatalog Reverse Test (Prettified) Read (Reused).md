
----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1512.69 | 0.073519 | 9728.25ms | 1151920 | 160 | 4.56106e+07 | 726229 | 0.0597104 | 3.37882 | 16.5608 | 3.26693 | 0.00741917 | 0.0351472 | 8.33391e-06 | 1(Win) | true |
| simdjson (ondemand) | 968.527 | 0.106479 | 7410.93ms | 1151920 | 80 | 1.16691e+08 | 1.13426e+06 | 0.0311616 | 5.25983 | 28.6298 | 5.58497 | 0.0116193 | 0.0828316 | 9.26714e-06 | 2(Loss) | true |
