
----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2413.11 | 0.0175492 | 8636.06ms | 409725 | 1280 | 1.0336e+06 | 161925 | 0.0144727 | 2.09673 | 9.77072 | 1.84457 | 0.00590341 | 0.000167059 | 1.99638e-06 | 1(Win) | true |
| simdjson (ondemand) | 1917.69 | 0.0397368 | 5372.3ms | 409725 | 320 | 2.09779e+06 | 203757 | 0.000299068 | 2.63604 | 11.0923 | 1.81361 | 0.00946118 | 0.00290799 | 4.60675e-06 | 2(Loss) | true |
