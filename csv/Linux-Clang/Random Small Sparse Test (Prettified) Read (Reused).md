
----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4157.33 | 0.139228 | 917.351ms | 8150 | 40 | 271.02 | 1869.58 | 0.0512332 | 1.26697 | 5.51252 | 0.903067 | 0.00174233 | 5.21472e-05 | 2.45399e-05 | 1(Win) | true |
| simdjson (ondemand) | 3602.93 | 0.0540639 | 946.467ms | 8150 | 2560 | 3482.24 | 2157.26 | 0.439125 | 1.45255 | 6.19288 | 0.887485 | 0.00172215 | 2.41085e-05 | 6.03911e-06 | 2(Loss) | true |
