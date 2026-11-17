
----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6639.22 | 0.0714802 | 766.411ms | 3770 | 4890 | 732.706 | 541.533 | 0.300995 | 0.832143 | 3.36313 | 0.390982 | 0.000265577 | 1.86599e-05 | 4.06828e-06 | 1(Win) | true |
| simdjson (ondemand) | 6514.63 | 0.0384411 | 768.307ms | 3770 | 2560 | 115.222 | 551.889 | 0.103867 | 0.848275 | 3.47639 | 0.357029 | 0.000283592 | 3.45035e-05 | 9.01442e-06 | 2(Loss) | true |
