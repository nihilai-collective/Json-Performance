
----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 18076.6 | 0.0942275 | 5474.8ms | 16197085 | 80 | 5.18662e+07 | 854514 | 0.00179199 | 0.280145 | 1.33981 | 0.0717036 | 9.33833e-05 | 0.0157387 | 0.00023891 | 1(Win) | true |
| simdjson (ondemand) | 16793.7 | 0.0797945 | 5860.85ms | 16197085 | 320 | 1.72376e+08 | 919794 | 0.302928 | 0.302639 | 1.33731 | 0.0899315 | 0.000108757 | 0.0157564 | 0.000212362 | 2(Loss) | true |
