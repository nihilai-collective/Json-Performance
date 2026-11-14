
----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18159 | 0.151058 | 4533.58ms | 716365 | 1280 | 4.13414e+06 | 37622.1 | 0.0978899 | 0.278162 | 1.02706 | 0.178553 | 0.000217005 | 0.00530255 | 8.84348e-06 | 1(Win) | true |
| Glaze | 4478.06 | 0.186859 | 8240.5ms | 716365 | 1280 | 1.04022e+08 | 152561 | 0.0735972 | 1.12389 | 2.81749 | 0.463529 | 0.000564553 | 0.0459144 | 6.76571e-05 | 2(Loss) | true |
