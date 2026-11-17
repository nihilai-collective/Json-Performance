
----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1470.45 | 0.109788 | 1041.04ms | 4604 | 4890 | 52551.8 | 2985.96 | 0.00749607 | 3.48832 | 9.36143 | 0.661599 | 0.000515156 | 0.000208985 | 0.000123037 | 1(Win) | true |
| Glaze | 828.375 | 0.0557994 | 1274.64ms | 4604 | 4890 | 42774.4 | 5300.4 | 0.147854 | 6.1559 | 12.9944 | 1.08775 | 0.00154462 | 0.000108823 | 4.57502e-05 | 2(Loss) | true |
