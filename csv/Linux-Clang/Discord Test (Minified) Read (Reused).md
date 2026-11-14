
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3174.85 | 0.0902199 | 2814.63ms | 56369 | 1280 | 298710 | 16932.4 | 0.0146656 | 1.59666 | 7.22391 | 1.40743 | 0.00355386 | 1.16143e-05 | 4.97558e-06 | 1(Win) | true |
| Glaze | 2966.09 | 0.0820835 | 2926.72ms | 56369 | 2560 | 566583 | 18124.1 | 0.0895041 | 1.70754 | 9.19944 | 1.77892 | 0.00237044 | 1.352e-05 | 5.68935e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2389.16 | 0.0371963 | 3350.62ms | 56369 | 4890 | 342530 | 22500.6 | 0.0873623 | 2.11931 | 10.1417 | 1.79114 | 0.00271294 | 2.86855e-05 | 1.70727e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1112.05 | 0.0837218 | 5993.33ms | 56369 | 4890 | 8.00979e+06 | 48341.2 | 0.0495381 | 4.51584 | 19.5776 | 3.09391 | 0.00936469 | 0.000103314 | 6.93103e-05 | 4(Loss) | true |
