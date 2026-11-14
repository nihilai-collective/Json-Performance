
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3123.79 | 0.0543787 | 6552.51ms | 183677 | 2560 | 2.38036e+06 | 56075.4 | 0.0468945 | 1.61894 | 7.28992 | 1.17634 | 0.00159773 | 1.62692e-05 | 1.06441e-05 | 1(Win) | true |
| Glaze | 2756.38 | 0.0915454 | 7295.93ms | 183677 | 4890 | 1.65506e+07 | 63550 | 0.138338 | 1.83481 | 8.80643 | 1.62996 | 0.00294072 | 1.72527e-05 | 1.13552e-05 | 2(Loss) | true |
| Jsonifier | 2327.6 | 0.0651474 | 8462.85ms | 183677 | 4890 | 1.17542e+07 | 75256.9 | 0.0142801 | 2.17121 | 7.95927 | 1.78205 | 0.00224209 | 2.73887e-05 | 1.78004e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1320.14 | 0.0585566 | 7282.47ms | 183677 | 2560 | 1.54548e+07 | 132689 | 0.0692095 | 3.80907 | 16.9149 | 2.57604 | 0.00223339 | 3.28596e-05 | 2.37382e-05 | 4(Loss) | true |
