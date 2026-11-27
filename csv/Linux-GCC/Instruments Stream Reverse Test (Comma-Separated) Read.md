
----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 983.358 | 1.1078 | 6262.22ms | 4197495 | 40 | 8.1346e+10 | 4.07079e+06 | 0.221411 | 5.14799 | 26.5403 | 5.39731 | 0.00120321 | 0.0840136 | 0.00513591 | 1(Win) | true |
| simdjson (ondemand) | 638.461 | 0.53224 | 9603.69ms | 4197495 | 80 | 8.90875e+10 | 6.26983e+06 | 0.0932383 | 7.94165 | 35.9299 | 7.10156 | 0.00971605 | 0.102242 | 0.00744842 | 2(Loss) | true |
