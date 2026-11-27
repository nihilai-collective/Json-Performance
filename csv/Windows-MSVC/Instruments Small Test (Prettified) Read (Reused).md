
----
### Instruments Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2946.27 | 0.144672 | 283.598ms | 7932 | 160 | 2207.55 | 2567.5 | 0.868726 | 1.02532 | 1(Win) | true |
| Jsonifier (two-stage) | 2570.06 | 0.312634 | 321.416ms | 7932 | 30 | 2540.23 | 2943.33 | 0 | 1.17134 | 2(Loss) | true |
| Glaze | 1931.83 | 0.709323 | 411.549ms | 7932 | 2560 | 1.97495e+06 | 3915.74 | 0.150861 | 1.5655 | 3(Loss) | true |
| simdjson (ondemand) | 1572.26 | 0.531958 | 505.288ms | 7932 | 80 | 52403.5 | 4811.25 | 0.542636 | 1.92579 | 4(Loss) | true |
