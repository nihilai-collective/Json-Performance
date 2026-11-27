
----
### Twitter Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8592.1 | 0.154217 | 4757.69ms | 360584 | 2560 | 9.75254e+06 | 40022.8 | 0.0830439 | 0.586893 | 2.96668 | 0.356613 | 0.000807624 | 1.0637e-05 | 6.25613e-06 | 1(Win) | true |
| simdjson (ondemand) | 7446.64 | 0.0713484 | 5388.94ms | 360584 | 40 | 43423.1 | 46179.2 | 0.047744 | 0.679173 | 3.29781 | 0.335419 | 0.000943261 | 1.66397e-06 | 1.10931e-06 | 2(Loss) | true |
