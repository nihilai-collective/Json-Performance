
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 562.854 | 0.0476707 | 1514.43ms | 4604 | 640 | 8850.4 | 7800.82 | 0.110487 | 9.19657 | 36.3228 | 7.71786 | 0.0125166 | 5.09068e-05 | 1.28964e-05 | 1(Win) | true |
| simdjson (ondemand) | 544.367 | 0.034479 | 1531.01ms | 4604 | 2560 | 19798.7 | 8065.72 | 0.0402148 | 9.50391 | 38.9056 | 7.06788 | 0.0104344 | 0.000129897 | 5.61672e-05 | 2(Loss) | true |
