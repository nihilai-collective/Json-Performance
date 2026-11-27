
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2006.17 | 0.31943 | 775.4ms | 1213 | 640 | 2171.27 | 576.623 | 0.125619 | 2.73928 | 14.634 | 2.6249 | 0.00158826 | 0.0002821 | 0.000109491 | 1(Win) | true |
| Glaze | 1143.14 | 0.111114 | 820.884ms | 1213 | 4890 | 6182.6 | 1011.96 | 0.638395 | 4.67379 | 25.3553 | 3.50701 | 0.00112753 | 0.000101828 | 1.95564e-05 | 2(Loss) | true |
| simdjson (ondemand) | 374.307 | 0.0518615 | 1030.37ms | 1213 | 4890 | 12562.2 | 3090.53 | 0.103899 | 13.9363 | 57.8897 | 11.7164 | 0.015284 | 0.000159317 | 2.71429e-05 | 3(Loss) | true |
