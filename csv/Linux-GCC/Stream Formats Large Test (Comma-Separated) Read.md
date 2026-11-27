
----
### Stream Formats Large Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 19691.7 | 0.170098 | 10209.8ms | 16197085 | 320 | 5.69711e+08 | 784430 | 0.0206043 | 0.258602 | 1.2466 | 0.0707847 | 7.00693e-05 | 0.0157375 | 0.000656157 | 1(Win) | true |
| simdjson (ondemand) | 14219.8 | 0.799809 | 6909.75ms | 16197085 | 160 | 1.20775e+10 | 1.08628e+06 | 1.8394 | 0.356302 | 1.4183 | 0.0987389 | 9.47705e-05 | 0.015752 | 0.0030645 | 2(Loss) | true |
