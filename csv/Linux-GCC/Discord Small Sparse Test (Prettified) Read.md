
----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4972.24 | 0.221593 | 847.427ms | 6701 | 40 | 324.449 | 1285.25 | 0.0947535 | 1.06771 | 4.49291 | 0.641098 | 0.000149231 | 1.49231e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4745.66 | 0.0778163 | 855.94ms | 6701 | 320 | 351.379 | 1346.61 | 0.0761749 | 1.11855 | 4.76004 | 0.625429 | 0.000152962 | 3.31107e-05 | 1.67885e-05 | 2(Loss) | true |
