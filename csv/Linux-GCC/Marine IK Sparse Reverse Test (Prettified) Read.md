
----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7745.57 | 0.141875 | 5761.17ms | 7351818 | 320 | 5.27773e+08 | 905194 | 0.0315388 | 0.661359 | 2.94525 | 0.432024 | 0.00200398 | 0.0635564 | 2.64348e-06 | 1(Win) | true |
| simdjson (ondemand) | 6052.69 | 0.332139 | 7355.17ms | 7351818 | 40 | 5.92094e+08 | 1.15837e+06 | 0.0580882 | 0.842523 | 4.22114 | 0.606512 | 0.0010852 | 0.0847961 | 2.56365e-05 | 2(Loss) | true |
