
----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2846.23 | 0.143864 | 845.736ms | 3770 | 1280 | 4227.26 | 1263.2 | 0.199917 | 1.86569 | 6.8037 | 1.14514 | 0.000543352 | 0.000101749 | 4.04095e-05 | 1(Win) | true |
| simdjson (ondemand) | 2616.41 | 0.094904 | 857.125ms | 3770 | 2560 | 4353.92 | 1374.16 | 0.0818866 | 2.01933 | 7.45783 | 1.18435 | 0.000272091 | 4.28962e-05 | 8.49635e-06 | 2(Loss) | true |
