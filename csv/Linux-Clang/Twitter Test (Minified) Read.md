
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1988.45 | 0.114391 | 5898.08ms | 466906 | 1280 | 8.39893e+07 | 223932 | 0.176536 | 2.53987 | 7.33108 | 1.40113 | 0.0115044 | 0.0160022 | 0.000120159 | 1(Win) | true |
| Glaze | 1864.68 | 0.105354 | 6308.91ms | 466906 | 640 | 4.05068e+07 | 238795 | 0.118573 | 2.71834 | 10.058 | 1.80149 | 0.0121299 | 0.0120931 | 9.16974e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1614.48 | 0.370143 | 7268.12ms | 466906 | 30 | 3.12649e+07 | 275802 | 0.0539709 | 3.12825 | 9.74104 | 1.58398 | 0.0205671 | 0.0304518 | 0.000118939 | 3(Loss) | true |
| simdjson (ondemand) | 923.668 | 0.267804 | 6244.1ms | 466906 | 80 | 1.33338e+08 | 482074 | 0.0897269 | 5.44121 | 18.6804 | 3.16318 | 0.0129579 | 0.045863 | 0.000150619 | 4(Loss) | true |
