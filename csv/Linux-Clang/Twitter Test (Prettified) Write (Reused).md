
----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18310.6 | 0.127395 | 4494.83ms | 716365 | 4890 | 1.10478e+07 | 37310.5 | 0.0785245 | 0.275749 | 1.02629 | 0.17838 | 0.000201902 | 0.00372329 | 9.2737e-06 | 1(Win) | true |
| Glaze | 5819.17 | 0.186951 | 6378.38ms | 716365 | 1280 | 6.16613e+07 | 117401 | 0.174006 | 0.86019 | 2.80754 | 0.461218 | 0.00058373 | 0.00350076 | 5.39693e-05 | 2(Loss) | true |
