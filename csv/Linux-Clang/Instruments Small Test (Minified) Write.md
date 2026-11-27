
----
### Instruments Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11420.4 | 0.136668 | 769.337ms | 4669 | 4890 | 1388.44 | 389.889 | 0.782923 | 0.48702 | 1.6209 | 0.232598 | 0.000272257 | 1.4848e-05 | 2.32136e-06 | 1(Win) | true |
| Glaze | 2537.59 | 0.17197 | 914.548ms | 4669 | 4890 | 44526.4 | 1754.7 | 0.833209 | 2.03892 | 3.66588 | 0.505034 | 0.000218208 | 3.29371e-05 | 7.70868e-06 | 2(Loss) | true |
