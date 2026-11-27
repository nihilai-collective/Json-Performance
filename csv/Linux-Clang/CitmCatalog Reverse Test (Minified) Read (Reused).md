
----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 749.24 | 0.0571383 | 8661.36ms | 500299 | 320 | 4.23665e+07 | 636808 | 0.111829 | 6.78636 | 34.7038 | 7.1929 | 0.0161218 | 0.00713781 | 0.000120291 | 1(Win) | true |
| simdjson (ondemand) | 430.614 | 0.0759032 | 7258.14ms | 500299 | 320 | 2.26336e+08 | 1.10801e+06 | 0.192154 | 11.829 | 64.4396 | 12.7984 | 0.0281297 | 0.0130379 | 0.000526273 | 2(Loss) | true |
