
----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10512.4 | 0.128597 | 757.048ms | 2963 | 40 | 4.77949 | 268.8 | 0.0372162 | 0.554151 | 1.30948 | 0.201822 | 0.000337496 | 8.43739e-06 | 0 | 1(Win) | true |
| Glaze | 4419.57 | 0.437191 | 799.767ms | 2963 | 1280 | 10001.3 | 639.369 | 0.176265 | 1.21915 | 2.73068 | 0.379345 | 0.000339869 | 3.40132e-05 | 4.74603e-06 | 2(Loss) | true |
