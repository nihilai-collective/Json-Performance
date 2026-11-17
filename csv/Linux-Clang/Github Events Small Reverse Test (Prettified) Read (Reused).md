
----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1171.56 | 0.0466594 | 904.26ms | 2158 | 2560 | 1719.86 | 1756.66 | 0.0377946 | 4.49509 | 16.1214 | 3.20621 | 0.00266975 | 0.000100824 | 1.82823e-05 | 1(Win) | true |
| simdjson (ondemand) | 946.048 | 0.0454399 | 947.344ms | 2158 | 1280 | 1250.72 | 2175.4 | 0.144615 | 5.54755 | 22.5144 | 3.91474 | 0.00166604 | 8.07316e-05 | 1.23089e-05 | 2(Loss) | true |
