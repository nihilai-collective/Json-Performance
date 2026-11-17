
----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1367.23 | 0.620401 | 8860.75ms | 1834197 | 40 | 2.52009e+09 | 1.2794e+06 | 2.30534 | 1(Win) | true |
| Glaze | 773.974 | 1.24142 | 7135.67ms | 1833577 | 30 | 2.35996e+10 | 2.25929e+06 | 1.3797 | 2(Loss) | true |
| simdjson (reflection) | 630.966 | 1.89833 | 8563.21ms | 1922245 | 30 | 9.12576e+10 | 2.90538e+06 | 1.18579 | 3(Loss) | true |
