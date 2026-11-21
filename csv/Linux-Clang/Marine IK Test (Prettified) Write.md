
----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5148.38 | 0.0694938 | 5776.87ms | 10018896 | 160 | 2.6614e+08 | 1.85588e+06 | 0.4498 | 0.480875 | 1(Win) | true |
| Glaze | 3239.6 | 0.142982 | 9160.57ms | 9930228 | 160 | 2.79525e+09 | 2.92326e+06 | 1.07525 | 0.764178 | 2(Loss) | true |
