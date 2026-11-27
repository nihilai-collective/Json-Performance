
----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 938.266 | 0.0984964 | 931.431ms | 1997 | 4890 | 19545.8 | 2029.79 | 0.121855 | 5.58016 | 17.8127 | 1.04106 | 0.000520105 | 8.32537e-05 | 6.14419e-06 | 1(Win) | true |
| Glaze | 673.708 | 0.12941 | 990.666ms | 1798 | 1280 | 13886.1 | 2545.18 | 0.0259922 | 7.77076 | 26.4321 | 2.17241 | 0.000831219 | 0.000121663 | 3.69334e-05 | 2(Loss) | true |
