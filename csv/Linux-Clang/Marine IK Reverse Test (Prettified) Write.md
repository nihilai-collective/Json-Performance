
----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5332.72 | 0.0869672 | 5520.55ms | 9930848 | 30 | 7.15661e+07 | 1.77598e+06 | 0.0492591 | 0.464249 | 1(Win) | true |
| Glaze | 3647.05 | 0.203712 | 8063.07ms | 9930228 | 80 | 2.23852e+09 | 2.59668e+06 | 0.285253 | 0.678817 | 2(Loss) | true |
