
----
### Instruments Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18815.8 | 0.0683092 | 1821.26ms | 213963 | 2560 | 140486 | 10844.7 | 0.097215 | 0.271519 | 1.25751 | 0.220674 | 0.000218079 | 1.25168e-05 | 9.1119e-06 | 1(Win) | true |
| Glaze | 5541.73 | 0.22275 | 4419.14ms | 213963 | 320 | 2.15264e+06 | 36820.8 | 0.078147 | 0.906421 | 3.61276 | 0.591747 | 0.000660511 | 1.10124e-05 | 6.32411e-06 | 2(Loss) | true |
