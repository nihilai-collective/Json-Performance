
----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1852.79 | 0.398405 | 7606.21ms | 4219119 | 80 | 5.98868e+09 | 2.17168e+06 | 0.0178016 | 2.73473 | 10.2104 | 1.85267 | 0.0150106 | 0.0564483 | 0.000810089 | 1(Win) | true |
| simdjson (ondemand) | 1444.35 | 0.115723 | 9487.12ms | 4219119 | 30 | 3.11787e+08 | 2.7858e+06 | 0.440067 | 3.48598 | 11.8716 | 2.29447 | 0.0187356 | 0.0539937 | 0.00130654 | 2(Loss) | true |
