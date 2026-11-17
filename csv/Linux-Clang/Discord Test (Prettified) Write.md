
----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16494.9 | 0.206624 | 1297.04ms | 94370 | 320 | 40670.2 | 5456.12 | 0.0293735 | 0.308525 | 1.28166 | 0.241708 | 0.000232529 | 3.17898e-06 | 7.6163e-07 | 1(Win) | true |
| Glaze | 4073.24 | 0.0721194 | 2969.35ms | 94370 | 2560 | 650028 | 22095 | 0.155649 | 1.23533 | 4.17651 | 0.677853 | 0.00193001 | 1.5721e-05 | 8.0592e-06 | 2(Loss) | true |
