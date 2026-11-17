
----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14339.7 | 0.490942 | 6344.29ms | 7351818 | 160 | 9.2191e+08 | 488938 | 0.302609 | 0.352516 | 1.58341 | 0.0601814 | 0.00169994 | 0.0211685 | 0.000133606 | 1(Win) | true |
| simdjson (stage-1) | 13654.4 | 0.19589 | 6685.03ms | 7351818 | 30 | 3.03522e+07 | 513479 | 0.330008 | 0.373683 | 1.77309 | 0.066041 | 0.00105792 | 0.021186 | 3.48667e-06 | 2(Loss) | true |
