
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3098.78 | 0.757112 | 5035.23ms | 1151920 | 640 | 4.61067e+09 | 354513 | 0.0671075 | 1.62567 | 7.52153 | 1.2748 | 0.00430095 | 0.0299137 | 1.42385e-05 | 1(Win) | true |
| simdjson (ondemand) | 2749.21 | 0.15058 | 5671ms | 1151920 | 40 | 1.44819e+07 | 399590 | 0.0211589 | 1.84192 | 7.98487 | 1.20338 | 0.00807567 | 0.0303145 | 5.49083e-06 | 2(Loss) | true |
