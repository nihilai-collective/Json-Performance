
----
### Random Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4061.65 | 0.0960647 | 909.379ms | 8150 | 160 | 540.703 | 1913.62 | 0.137036 | 1.27391 | 5.63804 | 0.93816 | 0.000657975 | 9.96933e-06 | 4.60123e-06 | 1(Win) | true |
| simdjson (ondemand) | 3389.58 | 0.0450873 | 950.102ms | 8150 | 4890 | 5226.86 | 2293.04 | 0.126234 | 1.53749 | 6.44479 | 0.990675 | 0.000954897 | 2.41133e-05 | 8.0545e-06 | 2(Loss) | true |
