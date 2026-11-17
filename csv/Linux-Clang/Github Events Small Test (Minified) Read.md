
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1265.2 | 0.0564333 | 843.231ms | 1691 | 4890 | 2530.16 | 1274.63 | 0.155169 | 4.20596 | 14.9072 | 2.93081 | 0.00116387 | 0.000345991 | 0.000142702 | 1(Win) | true |
| simdjson (ondemand) | 1176.68 | 0.0376435 | 854.139ms | 1691 | 4890 | 1301.54 | 1370.52 | 0.0123555 | 4.51072 | 16.9119 | 2.93554 | 0.000982466 | 9.33609e-05 | 6.89322e-06 | 2(Loss) | true |
