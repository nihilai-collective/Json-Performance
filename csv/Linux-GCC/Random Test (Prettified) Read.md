
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1997.15 | 0.101301 | 8430.33ms | 676745 | 640 | 6.85859e+07 | 323157 | 0.0515345 | 2.52363 | 11.4884 | 2.13914 | 0.00601399 | 0.0295791 | 5.09331e-05 | 1(Win) | true |
| simdjson (ondemand) | 1546.71 | 0.0913505 | 5400ms | 676745 | 80 | 1.16236e+07 | 417268 | 0.12863 | 3.27214 | 12.6557 | 2.31827 | 0.0107286 | 0.0383922 | 0.000106078 | 2(Loss) | true |
