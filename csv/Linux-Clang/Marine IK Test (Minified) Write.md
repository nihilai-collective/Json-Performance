
----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1130.43 | 0.583699 | 9817.22ms | 1834197 | 320 | 2.61054e+10 | 1.54739e+06 | 0.184974 | 4.46665 | 12.5598 | 0.909544 | 0.00140574 | 0.0596402 | 0.000178789 | 1(Win) | true |
| Glaze | 628.507 | 0.336535 | 8649ms | 1833577 | 160 | 1.40268e+10 | 2.7822e+06 | 0.187504 | 7.99938 | 16.0115 | 0.996585 | 0.000996297 | 0.0818108 | 0.000793129 | 2(Loss) | true |
