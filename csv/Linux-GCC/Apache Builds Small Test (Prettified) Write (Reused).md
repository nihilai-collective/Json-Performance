
----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15523.8 | 0.137766 | 737.087ms | 3643 | 2560 | 243.361 | 223.801 | 0.458502 | 0.392703 | 1.29701 | 0.181718 | 0.000274713 | 3.63497e-05 | 2.61632e-05 | 1(Win) | true |
| Glaze | 4897.13 | 0.45158 | 796.95ms | 3682 | 80 | 838.771 | 717.038 | 0.33408 | 1.10969 | 3.92205 | 0.637154 | 0.000271592 | 1.69745e-05 | 3.39489e-06 | 2(Loss) | true |
| simdjson (reflection) | 531.88 | 0.206615 | 1387.73ms | 3643 | 640 | 116572 | 6531.99 | 0.306987 | 9.50735 | 36.0458 | 7.55573 | 0.0159218 | 0.000229035 | 0.000135963 | 3(Loss) | true |
