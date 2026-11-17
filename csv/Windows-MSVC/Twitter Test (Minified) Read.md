
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1124.06 | 1.05955 | 5007.22ms | 466906 | 640 | 1.12748e+10 | 396133 | 0.0461706 | 2.7033 | 1(Win) | true |
| Glaze | 1020.02 | 0.920674 | 5604.64ms | 466906 | 640 | 1.0338e+10 | 436539 | 0.105228 | 2.97919 | 2(Loss) | true |
| Jsonifier (two-stage) | 986.688 | 0.829197 | 5729.6ms | 466906 | 640 | 8.9618e+09 | 451284 | 0.100134 | 3.07974 | 3(Loss) | true |
| simdjson (ondemand) | 844.708 | 1.50429 | 6598.57ms | 466906 | 160 | 1.00607e+10 | 527136 | 0.0548071 | 3.59759 | 4(Loss) | true |
