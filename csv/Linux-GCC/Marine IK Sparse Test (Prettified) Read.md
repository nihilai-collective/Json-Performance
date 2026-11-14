
----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10083.5 | 0.0945513 | 8943.15ms | 7351818 | 320 | 1.38311e+08 | 695321 | 0.27466 | 0.50454 | 2.27778 | 0.23517 | 0.00143573 | 0.0423942 | 0.000293976 | 1(Win) | true |
| simdjson (ondemand) | 9633.86 | 0.0446238 | 9372.06ms | 7351818 | 640 | 6.74997e+07 | 727771 | 0.0131345 | 0.531699 | 2.64676 | 0.256657 | 0.000969951 | 0.0424154 | 0.000163291 | 2(Loss) | true |
