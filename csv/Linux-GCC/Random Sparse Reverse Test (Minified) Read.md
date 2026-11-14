
----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1872.2 | 0.04451 | 5520.75ms | 409725 | 640 | 5.52299e+06 | 208708 | 0.0366885 | 2.72646 | 13.0925 | 2.45643 | 0.00872305 | 0.00142432 | 8.24486e-06 | 1(Win) | true |
| simdjson (ondemand) | 1415 | 0.107685 | 7203.4ms | 409725 | 80 | 7.07415e+06 | 276144 | 0.0430658 | 3.59957 | 14.7661 | 2.67877 | 0.0117912 | 0.00336515 | 6.46775e-06 | 2(Loss) | true |
