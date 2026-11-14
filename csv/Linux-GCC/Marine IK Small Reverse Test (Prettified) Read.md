
----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1173.81 | 0.0325799 | 2212.29ms | 18245 | 1280 | 29853.7 | 14823.3 | 0.0279517 | 4.39386 | 18.003 | 3.78202 | 0.00594238 | 2.56063e-05 | 1.29316e-05 | 1(Win) | true |
| simdjson (ondemand) | 916.921 | 0.0783089 | 2614ms | 18245 | 80 | 17665.9 | 18976.3 | 0.121813 | 5.62871 | 27.5754 | 5.59885 | 0.00653467 | 7.53631e-06 | 0 | 2(Loss) | true |
