
----
### Marine IK Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5710.96 | 0.0326727 | 422.795ms | 24893 | 80 | 147.569 | 4156.89 | 0.190106 | 0.430918 | 1(Win) | true |
| Glaze | 3972.56 | 0.067177 | 596.278ms | 24579 | 30 | 471.357 | 5900.57 | 0.0446484 | 0.620678 | 2(Loss) | true |
