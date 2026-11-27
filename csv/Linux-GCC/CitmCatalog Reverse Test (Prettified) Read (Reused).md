
----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1629.42 | 0.117257 | 9139.06ms | 1151920 | 80 | 4.99973e+07 | 674202 | 0.143153 | 3.11949 | 15.5241 | 3.10073 | 0.00732679 | 0.0324013 | 2.87346e-05 | 1(Win) | true |
| simdjson (ondemand) | 972.749 | 0.12677 | 7431.09ms | 1151920 | 40 | 8.19856e+07 | 1.12933e+06 | 0.113399 | 5.22663 | 27.8167 | 5.60092 | 0.0126832 | 0.0802253 | 0.000124792 | 2(Loss) | true |
