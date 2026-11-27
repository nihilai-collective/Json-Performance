
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9593.41 | 0.0916159 | 7065.96ms | 631514 | 1280 | 4.2342e+06 | 62778.3 | 0.310491 | 0.526658 | 2.65194 | 0.321348 | 0.000792304 | 4.80814e-05 | 3.83627e-06 | 1(Win) | true |
| Jsonifier | 9552.47 | 0.0487366 | 7109.35ms | 631514 | 4890 | 4.61695e+06 | 63047.5 | 0.270349 | 0.524524 | 2.65194 | 0.321348 | 0.000716971 | 5.00715e-05 | 8.17006e-06 | 2(Loss) | true |
| simdjson (ondemand) | 8508.54 | 0.093298 | 7951.98ms | 631514 | 320 | 1.39557e+06 | 70782.8 | 0.00335103 | 0.602618 | 2.87999 | 0.290641 | 0.000573399 | 1.34894e-05 | 2.87504e-06 | 3(Loss) | true |
| Glaze | 4050.25 | 0.0221248 | 8003.25ms | 631514 | 2560 | 2.77078e+06 | 148697 | 0.0132765 | 1.25192 | 5.31281 | 0.936974 | 0.00121873 | 8.93624e-06 | 4.39173e-06 | 4(Loss) | true |
