
----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15830.6 | 0.0245664 | 5841.65ms | 837491 | 4890 | 751206 | 50452.5 | 0.0569628 | 0.319818 | 1.35618 | 0.257756 | 0.00044693 | 0.0170789 | 5.74532e-06 | 1(Win) | true |
| Glaze | 3924.64 | 0.237346 | 5436.17ms | 837491 | 160 | 3.73287e+07 | 203507 | 0.266141 | 1.28268 | 4.56906 | 0.770696 | 0.00620895 | 0.0562821 | 6.86575e-06 | 2(Loss) | true |
