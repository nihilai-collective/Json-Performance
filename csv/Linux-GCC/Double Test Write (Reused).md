
----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 960.528 | 0.0863576 | 921.69ms | 1997 | 320 | 938.182 | 1982.75 | 0.034032 | 5.47809 | 18.2639 | 0.948423 | 0.000500751 | 0.000226903 | 0.000117364 | 1(Win) | true |
| simdjson (reflection) | 844.59 | 0.160682 | 952.784ms | 1997 | 160 | 2100.47 | 2254.93 | 0.0266155 | 6.21408 | 19.2484 | 1.24286 | 0.00112043 | 5.32048e-05 | 2.19079e-05 | 2(Loss) | true |
| Glaze | 721.965 | 0.0771595 | 973.745ms | 1798 | 160 | 537.336 | 2375.06 | 0.0113142 | 7.39276 | 26.614 | 2.36263 | 0.000879449 | 0.000139043 | 8.69021e-05 | 3(Loss) | true |
