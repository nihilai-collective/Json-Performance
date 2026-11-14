
----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14668.2 | 0.0848086 | 3774ms | 461466 | 640 | 414368 | 30002.9 | 0.0377658 | 0.344478 | 1.61411 | 0.264108 | 0.000500247 | 0.00756095 | 4.22566e-06 | 1(Win) | true |
| Glaze | 3667.42 | 0.116008 | 6570.33ms | 461466 | 2560 | 4.96104e+07 | 120000 | 0.0292616 | 1.37283 | 5.36925 | 0.791549 | 0.00994509 | 0.0390602 | 1.66326e-05 | 2(Loss) | true |
