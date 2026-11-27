
----
### Marine IK Reverse Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1642.18 | 0.575352 | 1017.28ms | 4918 | 320 | 86407.3 | 2856.06 | 0.0553955 | 3.11397 | 8.95323 | 0.571169 | 0.000474024 | 8.19693e-05 | 2.35106e-05 | 1(Win) | true |
| Glaze | 835.613 | 0.208734 | 1262.61ms | 4604 | 320 | 38494.5 | 5254.49 | 0.00118945 | 6.10015 | 12.9915 | 1.08666 | 0.00153535 | 3.80104e-05 | 4.07255e-06 | 2(Loss) | true |
