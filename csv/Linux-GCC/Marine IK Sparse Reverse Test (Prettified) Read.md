
----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7892.27 | 0.127824 | 5661.24ms | 7351818 | 160 | 2.06313e+08 | 888368 | 0.112952 | 0.645749 | 2.97762 | 0.41013 | 0.00129582 | 0.063573 | 5.51819e-06 | 1(Win) | true |
| simdjson (ondemand) | 6028.54 | 0.148673 | 7369.8ms | 7351818 | 160 | 4.78353e+08 | 1.16301e+06 | 0.0594895 | 0.851573 | 4.22114 | 0.606513 | 0.00100006 | 0.0848024 | 0.000253685 | 2(Loss) | true |
