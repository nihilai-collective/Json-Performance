
----
### Marine IK Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9983.17 | 0.604465 | 8971.73ms | 7351818 | 30 | 5.40651e+08 | 702306 | 0.236891 | 0.512353 | 2.24539 | 0.257067 | 0.00192852 | 0.0423788 | 0.00022759 | 1(Win) | true |
| simdjson (ondemand) | 9393.98 | 0.157162 | 9780.78ms | 7351818 | 80 | 1.10072e+08 | 746355 | 0.257932 | 0.543813 | 2.64676 | 0.256657 | 0.00106452 | 0.0424151 | 1.50082e-05 | 2(Loss) | true |
