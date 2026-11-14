
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1298.89 | 0.0594632 | 841.723ms | 1691 | 1280 | 697.674 | 1241.57 | 0.0495458 | 4.09135 | 14.5843 | 2.81017 | 0.000714721 | 6.42187e-05 | 8.31609e-06 | 1(Win) | true |
| simdjson (ondemand) | 1232.95 | 0.052411 | 848.331ms | 1691 | 2560 | 1203.04 | 1307.97 | 0.0221647 | 4.30128 | 15.0414 | 2.82436 | 0.00170295 | 5.38236e-05 | 3.46504e-06 | 2(Loss) | true |
