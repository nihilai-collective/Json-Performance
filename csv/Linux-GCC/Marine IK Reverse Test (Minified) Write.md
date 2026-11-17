
----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1118.55 | 0.126676 | 9836.75ms | 1834197 | 40 | 1.56974e+08 | 1.56383e+06 | 0.0693672 | 2.21337 | 1(Win) | true |
| Glaze | 907.427 | 0.101478 | 5936.28ms | 1833577 | 80 | 3.05918e+08 | 1.92702e+06 | 0.775613 | 2.72838 | 2(Loss) | true |
| simdjson (reflection) | 715.247 | 0.293689 | 7652.02ms | 1922245 | 30 | 1.69982e+09 | 2.56303e+06 | 0.0225659 | 3.46147 | 3(Loss) | true |
