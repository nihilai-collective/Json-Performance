
----
### Github Events Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1105.03 | 0.0529781 | 907.967ms | 2158 | 2560 | 2492.23 | 1862.42 | 0.0108238 | 4.76091 | 16.9314 | 3.35357 | 0.00202408 | 0.000110056 | 4.43481e-05 | 1(Win) | true |
| simdjson (ondemand) | 907.154 | 0.137945 | 963.551ms | 2158 | 30 | 293.816 | 2268.67 | 0.0161596 | 5.78284 | 21.8772 | 4.23494 | 0.00152919 | 0.000108125 | 4.63392e-05 | 2(Loss) | true |
