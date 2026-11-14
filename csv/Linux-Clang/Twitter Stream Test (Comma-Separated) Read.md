
----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1856.66 | 0.0984599 | 7464ms | 4219119 | 80 | 3.6424e+08 | 2.16715e+06 | 0.0629814 | 2.75765 | 10.3099 | 1.89894 | 0.0122746 | 0.0567478 | 0.000278459 | 1(Win) | true |
| simdjson (ondemand) | 1440.36 | 0.0914134 | 9375.3ms | 4219119 | 80 | 5.21686e+08 | 2.79351e+06 | 0.12472 | 3.50089 | 12.1414 | 1.96019 | 0.0173462 | 0.0557095 | 3.27705e-05 | 2(Loss) | true |
