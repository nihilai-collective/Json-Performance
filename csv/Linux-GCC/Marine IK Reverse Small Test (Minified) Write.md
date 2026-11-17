
----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1499.37 | 0.0795314 | 302.763ms | 4604 | 30 | 162.723 | 2928.37 | 0.169318 | 1.63542 | 1(Win) | true |
| simdjson (reflection) | 1292.93 | 0.0260639 | 358.611ms | 4918 | 80 | 71.515 | 3627.56 | 0.162036 | 1.90081 | 2(Loss) | true |
| Glaze | 1032.2 | 0.112879 | 444.662ms | 4604 | 30 | 691.651 | 4253.73 | 0.379929 | 2.38331 | 3(Loss) | true |
