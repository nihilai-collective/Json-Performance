
----
### Twitter Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1866.66 | 0.0661655 | 7508.45ms | 4219119 | 160 | 3.25458e+08 | 2.15554e+06 | 0.311294 | 1.3263 | 1(Win) | true |
| simdjson (ondemand) | 1827.96 | 0.285796 | 7525.92ms | 4219119 | 40 | 1.583e+09 | 2.20118e+06 | 0.879385 | 1.35439 | 2(Loss) | true |
