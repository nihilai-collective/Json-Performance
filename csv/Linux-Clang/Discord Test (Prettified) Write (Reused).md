
----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16538.4 | 0.0801024 | 1293.5ms | 94370 | 2560 | 48642 | 5441.77 | 0.0532983 | 0.306934 | 1.27585 | 0.240384 | 0.000236205 | 5.97714e-06 | 2.52083e-06 | 1(Win) | true |
| Glaze | 4557.24 | 0.181254 | 2739.63ms | 94370 | 640 | 820012 | 19748.4 | 0.00208091 | 1.10613 | 4.12562 | 0.666091 | 0.0018926 | 1.08284e-05 | 5.21551e-06 | 2(Loss) | true |
