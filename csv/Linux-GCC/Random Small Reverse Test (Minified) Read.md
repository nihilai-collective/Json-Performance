
----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 815.887 | 0.0575033 | 1293.97ms | 4926 | 1280 | 14032.1 | 5757.91 | 0.00478938 | 6.3524 | 27.4206 | 5.50386 | 0.00915994 | 4.04423e-05 | 9.67443e-06 | 1(Win) | true |
| simdjson (ondemand) | 502.176 | 0.0295443 | 1655.68ms | 4926 | 2560 | 19555.3 | 9354.88 | 0.127045 | 10.2952 | 45.3632 | 9.09338 | 0.0204678 | 5.2575e-05 | 1.72871e-05 | 2(Loss) | true |
