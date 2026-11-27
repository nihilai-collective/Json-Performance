
----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2427.33 | 0.129723 | 1042.48ms | 7932 | 40 | 653.733 | 3116.4 | 0.069573 | 2.14972 | 8.36561 | 1.58938 | 0.00105585 | 3.78215e-05 | 1.26072e-05 | 1(Win) | true |
| simdjson (ondemand) | 2410.48 | 0.0923967 | 1043.22ms | 7932 | 1280 | 10761.7 | 3138.19 | 0.340173 | 2.15381 | 9.43318 | 1.45171 | 0.000783811 | 3.63441e-05 | 8.07646e-06 | 2(Loss) | true |
