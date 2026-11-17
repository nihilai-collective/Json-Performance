
----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10473.1 | 0.108495 | 5348.51ms | 500299 | 320 | 781759 | 45556.8 | 0.0374124 | 0.482639 | 2.16498 | 0.353521 | 0.00204124 | 0.00183909 | 5.53419e-06 | 1(Win) | true |
| Glaze | 5739.64 | 0.044829 | 9083.7ms | 500299 | 4890 | 6.79073e+06 | 83127.6 | 0.202894 | 0.872765 | 4.17823 | 0.582038 | 0.00110896 | 0.000828914 | 2.40621e-05 | 2(Loss) | true |
