
----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 739.364 | 0.0512107 | 8701.29ms | 500299 | 320 | 3.49474e+07 | 645314 | 0.131593 | 6.90428 | 35.5245 | 7.29491 | 0.0162225 | 0.00592767 | 1.5016e-05 | 1(Win) | true |
| simdjson (ondemand) | 440.988 | 0.123538 | 7076.75ms | 500299 | 80 | 1.42921e+08 | 1.08194e+06 | 0.00212008 | 11.6248 | 64.4342 | 12.8004 | 0.0270165 | 0.00650284 | 5.57167e-06 | 2(Loss) | true |
