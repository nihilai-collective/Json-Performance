
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2722.16 | 0.164154 | 6689ms | 631514 | 160 | 2.11037e+07 | 221243 | 0.0478917 | 1.84949 | 6.07669 | 0.833152 | 0.00947309 | 0.0147536 | 8.16589e-05 | 1(Win) | true |
| simdjson (reflection) | 2352.61 | 0.304625 | 7447.69ms | 631514 | 640 | 3.89205e+08 | 255996 | 0.623156 | 2.1292 | 7.1133 | 0.967306 | 0.00742122 | 0.0223807 | 5.30026e-05 | 2(Loss) | true |
| Jsonifier | 2327.34 | 0.22966 | 7538.39ms | 631514 | 640 | 2.26047e+08 | 258775 | 0.11683 | 2.16944 | 6.23465 | 1.09536 | 0.00746303 | 0.00640605 | 4.72302e-05 | 3(Loss) | true |
| Glaze | 2257.41 | 0.085085 | 7716.28ms | 631514 | 1280 | 6.59571e+07 | 266792 | 0.13221 | 2.23831 | 8.23282 | 1.47676 | 0.00629815 | 0.00548702 | 3.12196e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1740.99 | 0.354748 | 9798.64ms | 631514 | 320 | 4.81906e+08 | 345928 | 0.0885255 | 2.89456 | 9.11501 | 1.82989 | 0.00813683 | 0.0183452 | 2.94629e-05 | 5(Loss) | true |
