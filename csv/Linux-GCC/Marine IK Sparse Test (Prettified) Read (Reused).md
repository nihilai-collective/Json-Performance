
----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10215.1 | 0.0774102 | 8870.48ms | 7351818 | 640 | 1.80668e+08 | 686361 | 0.103298 | 0.500436 | 2.27773 | 0.235159 | 0.00136953 | 0.0423776 | 0.000188147 | 1(Win) | true |
| simdjson (ondemand) | 9640.74 | 0.11077 | 9247.63ms | 7351818 | 80 | 5.19161e+07 | 727251 | 0.0257479 | 0.530285 | 2.64671 | 0.256645 | 0.000969463 | 0.0424042 | 0.000140511 | 2(Loss) | true |
