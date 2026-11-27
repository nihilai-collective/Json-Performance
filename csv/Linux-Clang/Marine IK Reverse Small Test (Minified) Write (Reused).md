
----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1692.73 | 0.0981787 | 1009.04ms | 4918 | 4890 | 36186.5 | 2770.78 | 0.16302 | 3.05896 | 8.88634 | 0.555104 | 0.000472992 | 5.49295e-05 | 2.13314e-05 | 1(Win) | true |
| Glaze | 877.338 | 0.0699367 | 1238.17ms | 4604 | 2560 | 31360.8 | 5004.59 | 0.223186 | 5.86884 | 12.4472 | 0.970679 | 0.000832327 | 5.48945e-05 | 1.73083e-05 | 2(Loss) | true |
