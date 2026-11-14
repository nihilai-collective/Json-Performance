
----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 730.556 | 0.102656 | 7408.26ms | 1834197 | 80 | 4.83328e+08 | 2.39438e+06 | 0.195002 | 4.16001 | 1(Win) | true |
| Glaze | 666.594 | 0.0815347 | 8146.51ms | 1833577 | 160 | 7.31948e+08 | 2.62324e+06 | 0.241769 | 4.55923 | 2(Loss) | true |
