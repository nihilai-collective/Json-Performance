
----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14351.3 | 0.0792741 | 6309.82ms | 7351818 | 640 | 9.59959e+07 | 488546 | 0.0128017 | 0.350886 | 1.58341 | 0.0601814 | 0.00170032 | 0.0211487 | 0.00011783 | 1(Win) | true |
| simdjson (stage-1) | 13607.1 | 0.0877971 | 6652.73ms | 7351818 | 640 | 1.30978e+08 | 515262 | 0.200804 | 0.375578 | 1.77309 | 0.066041 | 0.00104619 | 0.0211862 | 0.000190253 | 2(Loss) | true |
