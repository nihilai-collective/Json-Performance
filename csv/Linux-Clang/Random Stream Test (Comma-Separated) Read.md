
----
### Random Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1175.42 | 1.39326 | 6182.8ms | 4506446 | 30 | 7.78517e+10 | 3.65629e+06 | 0.206871 | 4.30795 | 17.5071 | 3.3124 | 0.0196425 | 0.0811885 | 0.00710831 | 1(Win) | true |
| simdjson (ondemand) | 907.617 | 0.281875 | 7847.46ms | 4506446 | 80 | 1.42517e+10 | 4.73513e+06 | 1.44937 | 5.58409 | 21.5787 | 3.80993 | 0.01702 | 0.0864313 | 0.0124415 | 2(Loss) | true |
