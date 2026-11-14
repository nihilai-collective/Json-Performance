
----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6416.38 | 0.0929257 | 768.066ms | 3770 | 2560 | 694.087 | 560.339 | 0.122613 | 0.858259 | 3.3626 | 0.390982 | 0.000266392 | 1.89614e-05 | 8.28912e-07 | 1(Win) | true |
| simdjson (ondemand) | 6383.1 | 0.0307859 | 768.882ms | 3770 | 4890 | 147.039 | 563.261 | 0.045057 | 0.870173 | 3.4687 | 0.354377 | 0.000269266 | 1.93108e-05 | 4.82769e-06 | 2(Loss) | true |
