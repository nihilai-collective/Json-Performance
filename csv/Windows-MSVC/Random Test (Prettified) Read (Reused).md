
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1326.92 | 0.0279089 | 7752.59ms | 728486 | 640 | 1.36652e+07 | 523572 | 0.0053422 | 2.29041 | 1(Win) | true |
| Jsonifier | 1180 | 0.064072 | 8558.18ms | 728486 | 80 | 1.13842e+07 | 588760 | 0.0810369 | 2.57564 | 2(Loss) | true |
| Glaze | 1084.25 | 0.0790411 | 9249.28ms | 728486 | 160 | 4.10403e+07 | 640756 | 0.0749529 | 2.80313 | 3(Loss) | true |
| simdjson (ondemand) | 933.328 | 0.245992 | 5258.66ms | 728486 | 30 | 1.00586e+08 | 744367 | 0.226079 | 3.25627 | 4(Loss) | true |
