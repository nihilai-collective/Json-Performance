
----
### Discord Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12289.5 | 0.174043 | 799.254ms | 7376 | 2560 | 2540.56 | 572.385 | 0.172548 | 0.441853 | 1.52183 | 0.254745 | 0.000136051 | 1.60466e-05 | 4.97814e-06 | 1(Win) | true |
| Glaze | 2828.03 | 0.182591 | 985.257ms | 7376 | 2560 | 52804.8 | 2487.35 | 0.248085 | 1.83404 | 4.2523 | 0.667028 | 0.00055967 | 4.10961e-05 | 1.30279e-05 | 2(Loss) | true |
