
----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20555.4 | 0.0489426 | 1734.62ms | 213963 | 4890 | 115428 | 9926.9 | 0.0970447 | 0.247616 | 1.11647 | 0.274664 | 0.000181966 | 8.81792e-06 | 5.90378e-06 | 1(Win) | true |
| Glaze | 5761.16 | 0.158336 | 4294ms | 213963 | 640 | 2.0128e+06 | 35418.4 | 0.0345897 | 0.871063 | 3.61276 | 0.591747 | 0.000661709 | 7.62398e-06 | 3.61482e-06 | 2(Loss) | true |
