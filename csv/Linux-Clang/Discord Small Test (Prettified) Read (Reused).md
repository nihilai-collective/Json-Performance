
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2840.41 | 0.155386 | 995.844ms | 6701 | 80 | 977.756 | 2249.88 | 0.0400182 | 1.81387 | 7.49963 | 1.18102 | 0.000654753 | 5.96926e-05 | 2.42501e-05 | 1(Win) | true |
| Glaze | 2585.5 | 0.133283 | 1013.39ms | 6701 | 2560 | 27782.8 | 2471.7 | 0.0502501 | 1.98858 | 8.86703 | 1.67975 | 0.00120825 | 2.73397e-05 | 3.26444e-06 | 2(Loss) | true |
| Jsonifier | 1935.17 | 0.269579 | 1097.57ms | 6701 | 4890 | 387545 | 3302.33 | 0.30007 | 2.6472 | 8.42337 | 1.73556 | 0.00150293 | 5.08119e-05 | 1.5503e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1200.88 | 0.197154 | 1300.31ms | 6701 | 30 | 3302.25 | 5321.57 | 0.00375815 | 4.24646 | 15.2274 | 2.51022 | 0.00247724 | 2.98463e-05 | 2.48719e-05 | 4(Loss) | true |
