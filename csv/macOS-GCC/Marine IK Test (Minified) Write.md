
----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1315.48 | 0.28592 | 8732.09ms | 1834197 | 40 | 5.7819e+08 | 1.32972e+06 | 0.606116 | 1(Win) | true |
| Glaze | 792.972 | 1.60895 | 6996.08ms | 1833577 | 30 | 3.77648e+10 | 2.20517e+06 | 0.346296 | 2(Loss) | true |
| simdjson (reflection) | 719.229 | 0.791139 | 8121.97ms | 1922245 | 80 | 3.25296e+10 | 2.54884e+06 | 0.585992 | 3(Loss) | true |
