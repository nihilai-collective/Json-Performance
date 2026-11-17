
----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1539.53 | 0.0534846 | 9573.45ms | 1151920 | 320 | 4.661e+07 | 713568 | 0.0478591 | 3.29539 | 16.5617 | 3.26699 | 0.00713296 | 0.0345606 | 2.29264e-05 | 1(Win) | true |
| simdjson (ondemand) | 946.411 | 0.579686 | 7597.92ms | 1151920 | 160 | 7.24421e+09 | 1.16076e+06 | 0.471241 | 5.36099 | 28.6368 | 5.5872 | 0.0126107 | 0.0718637 | 4.33027e-05 | 2(Loss) | true |
