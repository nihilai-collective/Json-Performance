
----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19611.2 | 0.219262 | 3074.81ms | 475954 | 2560 | 6.5931e+06 | 23145.2 | 0.0583304 | 0.256779 | 1.01939 | 0.152775 | 0.000284155 | 0.000110544 | 4.61081e-06 | 1(Win) | true |
| Glaze | 6307.5 | 0.268075 | 7961.95ms | 475954 | 1280 | 4.76363e+07 | 71962.8 | 0.191514 | 0.795977 | 2.36354 | 0.337169 | 0.000356243 | 0.0104559 | 1.0236e-05 | 2(Loss) | true |
