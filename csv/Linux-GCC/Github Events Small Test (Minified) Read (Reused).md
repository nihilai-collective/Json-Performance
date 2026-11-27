
----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1551.73 | 0.0671269 | 829.769ms | 1691 | 320 | 155.739 | 1039.27 | 0.0607767 | 3.4442 | 12.469 | 2.30633 | 0.000591366 | 8.68569e-05 | 5.54406e-06 | 1(Win) | true |
| simdjson (ondemand) | 1382.89 | 0.0748608 | 844.698ms | 1691 | 2560 | 1951.02 | 1166.15 | 0.12158 | 3.8545 | 13.55 | 2.46482 | 0.00152508 | 8.82429e-05 | 1.70942e-05 | 2(Loss) | true |
