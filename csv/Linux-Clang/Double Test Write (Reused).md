
----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 895.766 | 0.376992 | 944.561ms | 1811 | 40 | 2113.35 | 1928.08 | 0.156646 | 5.87798 | 19.6096 | 1.14025 | 0.000552181 | 9.66317e-05 | 4.14136e-05 | 1(Win) | true |
| Glaze | 613.666 | 0.180432 | 1033.3ms | 1798 | 640 | 16267.5 | 2794.2 | 0.023156 | 8.36163 | 26.4321 | 2.17241 | 0.00074562 | 0.000158162 | 7.73429e-05 | 2(Loss) | true |
