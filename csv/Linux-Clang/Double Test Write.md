
----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 334.428 | 0.0299911 | 524.929ms | 1811 | 160 | 383.828 | 5164.36 | 0.137171 | 7.36606 | 1(Win) | true |
| Glaze | 285.197 | 0.116999 | 607.366ms | 1798 | 4890 | 241970 | 6012.37 | 0.133381 | 8.64382 | 2(Loss) | true |
