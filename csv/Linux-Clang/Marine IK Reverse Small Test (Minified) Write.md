
----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1338.2 | 0.105932 | 1066.26ms | 4604 | 2560 | 30926.1 | 3281.07 | 0.12643 | 3.8248 | 9.44309 | 0.661165 | 0.000574314 | 5.05674e-05 | 2.34171e-05 | 1(Win) | true |
| Glaze | 791.178 | 0.0729744 | 1296.01ms | 4604 | 4890 | 80199.6 | 5549.59 | 0.13483 | 6.4448 | 12.9939 | 1.08775 | 0.00154143 | 8.77249e-05 | 3.75774e-05 | 2(Loss) | true |
