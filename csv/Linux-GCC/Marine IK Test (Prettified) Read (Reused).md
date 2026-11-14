
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2902.39 | 0.141888 | 8248.41ms | 7351818 | 40 | 4.69929e+08 | 2.41568e+06 | 0.027943 | 1.72511 | 7.40591 | 1.33312 | 0.0104629 | 0.0546594 | 0.000125455 | 1(Win) | true |
| Jsonifier | 2853.7 | 0.043568 | 8373.14ms | 7351818 | 80 | 9.16641e+07 | 2.4569e+06 | 0.0631409 | 1.76916 | 7.88138 | 1.79323 | 0.00751715 | 0.027857 | 0.000288939 | 2(Loss) | true |
| simdjson (reflection) | 2485.78 | 0.0690645 | 9438.75ms | 7351818 | 40 | 1.51787e+08 | 2.82054e+06 | 0.00736734 | 2.03028 | 8.96023 | 1.48803 | 0.00784052 | 0.0521438 | 8.04631e-05 | 3(Loss) | true |
| Glaze | 2208.51 | 0.131833 | 5156.42ms | 7351818 | 40 | 7.00643e+08 | 3.17465e+06 | 0.161958 | 2.28329 | 10.4912 | 2.06524 | 0.00872886 | 0.0278544 | 0.000329816 | 4(Loss) | true |
| simdjson (ondemand) | 2093.84 | 0.113619 | 5387.24ms | 7351818 | 40 | 5.78981e+08 | 3.34851e+06 | 0.19251 | 2.40052 | 9.61118 | 1.69576 | 0.00908581 | 0.0537446 | 0.00010309 | 5(Loss) | true |
