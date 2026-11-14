
----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16306.2 | 0.060834 | 1303.21ms | 94370 | 30 | 338.202 | 5519.27 | 0.116426 | 0.312499 | 1.27585 | 0.240384 | 0.00023807 | 2.47254e-06 | 0 | 1(Win) | true |
| Glaze | 4490.46 | 0.090023 | 2763.81ms | 94370 | 2560 | 833363 | 20042.1 | 0.0889329 | 1.12046 | 4.12562 | 0.666091 | 0.00156796 | 1.33534e-05 | 6.62701e-06 | 2(Loss) | true |
