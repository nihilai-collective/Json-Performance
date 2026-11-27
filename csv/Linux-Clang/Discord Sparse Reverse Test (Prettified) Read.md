
----
### Discord Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2388.63 | 0.0668608 | 4082.83ms | 83958 | 320 | 160738 | 33520.7 | 0.193498 | 2.11993 | 9.43597 | 1.73693 | 0.0042646 | 2.02482e-05 | 1.28785e-05 | 1(Win) | true |
| simdjson (ondemand) | 1941.68 | 0.20771 | 4858.07ms | 83958 | 80 | 586914 | 41236.8 | 0.385631 | 2.63954 | 12.0049 | 1.93766 | 0.00521347 | 3.64766e-05 | 2.53103e-05 | 2(Loss) | true |
