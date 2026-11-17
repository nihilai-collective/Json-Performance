
----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1126.72 | 0.188544 | 9836.21ms | 1834197 | 30 | 2.57045e+08 | 1.5525e+06 | 0.127301 | 2.19731 | 1(Win) | true |
| Glaze | 905.841 | 0.131661 | 5956.97ms | 1833577 | 30 | 1.93789e+08 | 1.9304e+06 | 0.575695 | 2.73314 | 2(Loss) | true |
| simdjson (reflection) | 727.742 | 0.0615915 | 7849.54ms | 1922245 | 40 | 9.62865e+07 | 2.51902e+06 | 0.120411 | 3.40204 | 3(Loss) | true |
