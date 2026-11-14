
----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5004.53 | 0.0418957 | 9137ms | 1834197 | 640 | 1.37241e+07 | 349529 | 0.138831 | 1.02107 | 5.69891 | 0.827984 | 0.000707447 | 0.0756114 | 2.46106e-06 | 1(Win) | true |
| simdjson (ondemand) | 4290.58 | 0.0398044 | 5281.49ms | 1834197 | 640 | 1.6854e+07 | 407690 | 0.0552682 | 1.18441 | 6.52919 | 0.874485 | 0.00494846 | 0.0754727 | 4.59499e-06 | 2(Loss) | true |
