
----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 912.065 | 0.110392 | 5091.09ms | 360584 | 320 | 5.54355e+07 | 377034 | 0.23097 | 5.57487 | 21.0424 | 3.96863 | 0.0142182 | 0.00170635 | 2.23509e-05 | 1(Win) | true |
| simdjson (ondemand) | 460.308 | 0.0751136 | 9791.79ms | 360584 | 640 | 2.01527e+08 | 747064 | 0.0902196 | 10.9341 | 45.8805 | 9.22901 | 0.0494824 | 0.000270421 | 5.1817e-05 | 2(Loss) | true |
