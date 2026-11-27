
----
### Instruments Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 623.199 | 0.0353568 | 1439.57ms | 4669 | 2560 | 16337.3 | 7144.92 | 0.117488 | 8.28429 | 37.063 | 7.30392 | 0.00804776 | 7.23689e-05 | 2.84456e-05 | 1(Win) | true |
| simdjson (ondemand) | 239.048 | 0.048427 | 2589.11ms | 4669 | 640 | 52075.4 | 18626.8 | 0.10515 | 21.5303 | 94.6263 | 19.2632 | 0.056246 | 0.000121145 | 6.62615e-05 | 2(Loss) | true |
