
----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2176.5 | 0.0565391 | 8901.17ms | 676745 | 1280 | 3.59783e+07 | 296528 | 0.205867 | 2.32907 | 10.035 | 1.78189 | 0.00729673 | 0.00991544 | 2.91746e-05 | 1(Win) | true |
| simdjson (ondemand) | 1749.38 | 0.417504 | 5313.39ms | 676745 | 160 | 3.79597e+08 | 368927 | 0.0339518 | 2.89462 | 11.4448 | 1.89166 | 0.0105961 | 0.0157288 | 3.01905e-05 | 2(Loss) | true |
