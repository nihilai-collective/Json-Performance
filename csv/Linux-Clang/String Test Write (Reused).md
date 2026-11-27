
----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5392.16 | 0.116301 | 812.273ms | 4215 | 4890 | 3675.72 | 745.478 | 0.050568 | 1.00357 | 4.41186 | 0.567735 | 0.000978878 | 4.32286e-05 | 1.04797e-05 | 1(Win) | true |
| Glaze | 2180.01 | 0.0810884 | 930.062ms | 4215 | 4890 | 10932.1 | 1843.91 | 0.229524 | 2.40727 | 10.3618 | 1.5108 | 0.00143848 | 7.29695e-05 | 3.20697e-05 | 2(Loss) | true |
