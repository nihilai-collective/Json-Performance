
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11115.4 | 0.0295326 | 4748.63ms | 466906 | 4890 | 684418 | 40059.5 | 0.371162 | 0.45135 | 1.82507 | 0.102764 | 0.000454758 | 2.23247e-05 | 2.73436e-06 | 1(Win) | true |
| simdjson (ondemand) | 9102.38 | 0.0813718 | 5639.49ms | 466906 | 1280 | 2.02818e+06 | 48918.7 | 0.112273 | 0.556861 | 2.12607 | 0.0437391 | 6.54659e-05 | 0.000948821 | 3.71127e-06 | 2(Loss) | true |
| Glaze | 2623.81 | 0.243787 | 9026.13ms | 466906 | 40 | 6.84665e+06 | 169706 | 0.221543 | 1.91098 | 7.74608 | 1.47668 | 0.00253723 | 0.000639636 | 1.39214e-05 | 3(Loss) | true |
