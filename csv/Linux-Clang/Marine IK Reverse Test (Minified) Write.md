
----
### Marine IK Reverse Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1359.42 | 0.0912405 | 8495.94ms | 1922245 | 160 | 2.42217e+08 | 1.34851e+06 | 0.0038632 | 1.82117 | 1(Win) | true |
| Glaze | 671.394 | 0.108613 | 8215.49ms | 1833577 | 40 | 3.20084e+08 | 2.60448e+06 | 0.625429 | 3.68731 | 2(Loss) | true |
