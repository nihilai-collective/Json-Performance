
----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10284.1 | 0.0637894 | 8792.98ms | 7351818 | 640 | 1.21041e+08 | 681754 | 0.275122 | 0.49254 | 2.27778 | 0.23517 | 0.00133299 | 0.0423555 | 1.85579e-05 | 1(Win) | true |
| simdjson (ondemand) | 9532.35 | 0.166886 | 9536.04ms | 7351818 | 40 | 6.02681e+07 | 735521 | 0.128468 | 0.536101 | 2.64676 | 0.256657 | 0.000963969 | 0.0424192 | 0.000251921 | 2(Loss) | true |
