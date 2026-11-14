
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1366.68 | 0.0519665 | 1122.24ms | 5092 | 1280 | 4364.18 | 3553.22 | 0.0654566 | 3.81537 | 15.9089 | 2.92189 | 0.00232641 | 2.85374e-05 | 2.14798e-06 | 1(Win) | true |
| simdjson (ondemand) | 1293.79 | 0.0727546 | 1140.98ms | 5092 | 640 | 4772.57 | 3753.41 | 0.0159829 | 4.02407 | 16.3078 | 2.70066 | 0.00326738 | 3.95842e-05 | 3.37539e-06 | 2(Loss) | true |
