
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 845.282 | 0.0891004 | 6469.27ms | 1834197 | 80 | 2.71981e+08 | 2.0694e+06 | 0.0439614 | 5.95571 | 26.5404 | 5.63525 | 0.0310143 | 0.0824489 | 0.000409341 | 1(Win) | true |
| Jsonifier (two-stage) | 732.553 | 0.124044 | 7499.54ms | 1834197 | 80 | 7.01868e+08 | 2.38785e+06 | 0.228471 | 6.82868 | 30.584 | 6.18683 | 0.0366712 | 0.146256 | 0.000846263 | 2(Loss) | true |
| Glaze | 664.119 | 0.119489 | 8218.49ms | 1834197 | 80 | 7.92402e+08 | 2.63391e+06 | 0.0389242 | 7.54013 | 31.9798 | 6.48941 | 0.0356913 | 0.0821346 | 0.000927736 | 3(Loss) | true |
| simdjson (ondemand) | 560.691 | 0.506527 | 9706.98ms | 1834197 | 160 | 3.99549e+10 | 3.11977e+06 | 0.0356086 | 8.97437 | 37.2161 | 6.29552 | 0.0460608 | 0.147241 | 0.000973232 | 4(Loss) | true |
