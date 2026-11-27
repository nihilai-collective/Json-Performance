
----
### Discord Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4445.55 | 0.10373 | 823.263ms | 4857 | 640 | 747.603 | 1041.94 | 0.0223392 | 1.19862 | 5.24954 | 0.815524 | 0.000209105 | 9.00762e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3773.94 | 0.107833 | 845.28ms | 4857 | 80 | 140.133 | 1227.36 | 0.0499287 | 1.41023 | 5.93515 | 0.826848 | 0.000239345 | 7.72082e-06 | 0 | 2(Loss) | true |
