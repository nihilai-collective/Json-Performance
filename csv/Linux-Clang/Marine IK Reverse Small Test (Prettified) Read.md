
----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2470.63 | 0.13738 | 1447.33ms | 18245 | 1280 | 119820 | 7042.66 | 0.022058 | 2.05732 | 8.13944 | 1.5083 | 0.00176071 | 8.47835e-06 | 1.2846e-06 | 1(Win) | true |
| Jsonifier | 2163.41 | 0.0963797 | 1549.25ms | 18245 | 4890 | 293826 | 8042.76 | 0.265116 | 2.34554 | 8.96706 | 2.05733 | 0.00224655 | 2.17557e-05 | 8.75383e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1865.76 | 0.0716648 | 1677.85ms | 18245 | 2560 | 114348 | 9325.84 | 0.0498031 | 2.72033 | 11.1304 | 1.86665 | 0.00162746 | 2.78758e-05 | 9.91282e-06 | 3(Loss) | true |
| Glaze | 1781.91 | 0.143784 | 1726.36ms | 18245 | 160 | 31539.8 | 9764.7 | 0.00204824 | 2.84982 | 11.8155 | 2.3863 | 0.00418368 | 2.29515e-05 | 1.19896e-05 | 4(Loss) | true |
