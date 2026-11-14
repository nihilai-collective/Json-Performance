
----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1153.28 | 0.46042 | 9664.46ms | 1834197 | 30 | 1.46303e+09 | 1.51674e+06 | 0.124252 | 4.38058 | 12.5639 | 0.909542 | 0.00163928 | 0.0586708 | 0.000163468 | 1(Win) | true |
| Glaze | 640.785 | 0.209812 | 8525.28ms | 1833577 | 80 | 2.62257e+09 | 2.7289e+06 | 0.365528 | 7.89873 | 16.012 | 0.996538 | 0.00107222 | 0.0493935 | 0.000283878 | 2(Loss) | true |
