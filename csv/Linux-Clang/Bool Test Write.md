
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2298.73 | 0.261239 | 751.766ms | 905 | 1280 | 1231.42 | 375.457 | 1.0971 | 2.48181 | 9.3105 | 0.950277 | 0.00335808 | 7.07873e-05 | 3.45304e-06 | 1(Win) | true |
| Glaze | 222.889 | 0.0569994 | 1107.79ms | 905 | 4890 | 23821.6 | 3872.22 | 0.0509282 | 23.2275 | 112.869 | 22.9381 | 0.0754771 | 0.000354766 | 0.000154109 | 2(Loss) | true |
