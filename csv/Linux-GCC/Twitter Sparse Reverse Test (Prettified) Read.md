
----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5677.15 | 0.0243689 | 6779.33ms | 360584 | 4890 | 1.06545e+06 | 60572.6 | 0.0696265 | 0.899979 | 4.37729 | 0.666017 | 0.00145519 | 3.27122e-06 | 1.61576e-06 | 1(Win) | true |
| simdjson (ondemand) | 5003.04 | 0.07084 | 7656.49ms | 360584 | 320 | 758668 | 68734.2 | 0.0386621 | 1.01531 | 5.0398 | 0.715319 | 0.00186235 | 4.31592e-06 | 1.81996e-06 | 2(Loss) | true |
