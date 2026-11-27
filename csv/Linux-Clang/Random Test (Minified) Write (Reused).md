
----
### Random Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13923.8 | 0.120662 | 3942.77ms | 461466 | 640 | 930863 | 31606.8 | 0.0796992 | 0.362951 | 1.61249 | 0.233365 | 0.000588075 | 0.00823393 | 8.39377e-06 | 1(Win) | true |
| Glaze | 3952.87 | 0.145812 | 6100.78ms | 461466 | 2560 | 6.74651e+07 | 111334 | 0.180845 | 1.2731 | 5.35473 | 0.788156 | 0.00997021 | 0.00927129 | 5.02441e-05 | 2(Loss) | true |
