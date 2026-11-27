
----
### Twitter Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7537.43 | 0.027644 | 4080.68ms | 264040 | 4890 | 417065 | 33407.7 | 0.0352247 | 0.671817 | 3.39984 | 0.455567 | 0.00120345 | 1.95019e-06 | 8.94547e-07 | 1(Win) | true |
| simdjson (ondemand) | 6212.88 | 0.0539876 | 4859.24ms | 264040 | 320 | 153212 | 40530 | 0.151855 | 0.816903 | 3.97149 | 0.435095 | 0.00123798 | 4.53293e-06 | 2.52092e-06 | 2(Loss) | true |
