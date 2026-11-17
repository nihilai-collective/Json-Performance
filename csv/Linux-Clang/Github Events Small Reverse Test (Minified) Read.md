
----
### Github Events Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 940.853 | 0.0390196 | 890.148ms | 1691 | 320 | 143.139 | 1714.04 | 0.181918 | 5.60151 | 20.6487 | 4.16026 | 0.00119012 | 0.000112729 | 5.54406e-06 | 1(Win) | true |
| simdjson (ondemand) | 684.15 | 0.142565 | 962.338ms | 1691 | 320 | 3613.75 | 2357.18 | 0.200975 | 7.65328 | 30.2543 | 5.42697 | 0.00184432 | 0.000114577 | 3.14163e-05 | 2(Loss) | true |
