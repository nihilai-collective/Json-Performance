
----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14725.5 | 0.0380981 | 3763.26ms | 461466 | 4890 | 633950 | 29886.1 | 0.0243136 | 0.343289 | 1.61296 | 0.263851 | 0.000497109 | 0.00734272 | 1.15006e-05 | 1(Win) | true |
| Glaze | 4003.73 | 0.128756 | 6025.23ms | 461466 | 2560 | 5.1277e+07 | 109919 | 0.143675 | 1.25579 | 5.35474 | 0.788156 | 0.00993031 | 0.0127783 | 3.1927e-05 | 2(Loss) | true |
