
----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 335.723 | 0.0504423 | 1244.1ms | 1811 | 4890 | 32928.6 | 5144.44 | 0.0163073 | 15.2728 | 64.0276 | 11.3992 | 0.0181285 | 0.00010016 | 2.04386e-05 | 1(Win) | true |
| Glaze | 300.781 | 0.124294 | 1304.11ms | 1798 | 1280 | 64267 | 5700.85 | 0.495797 | 16.9886 | 71.2742 | 12.1413 | 0.0206379 | 0.000176846 | 8.64676e-05 | 2(Loss) | true |
