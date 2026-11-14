
----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5630.84 | 0.139451 | 5247.37ms | 9930848 | 160 | 8.80219e+08 | 1.68195e+06 | 0.111158 | 1(Win) | true |
| Glaze | 2999.6 | 0.0925913 | 9841.68ms | 9930228 | 160 | 1.36726e+09 | 3.15716e+06 | 0.007657 | 2(Loss) | true |
