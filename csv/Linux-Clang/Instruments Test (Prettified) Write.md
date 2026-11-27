
----
### Instruments Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18613 | 0.074032 | 1842.78ms | 213963 | 2560 | 168626 | 10962.9 | 0.218798 | 0.275843 | 1.25997 | 0.22123 | 0.000216681 | 3.92883e-06 | 1.6431e-06 | 1(Win) | true |
| Glaze | 4835.27 | 0.0485991 | 4979.11ms | 213963 | 4890 | 2.05685e+06 | 42200.6 | 0.0312068 | 1.04733 | 3.63887 | 0.597758 | 0.000657381 | 2.95896e-05 | 1.43929e-05 | 2(Loss) | true |
