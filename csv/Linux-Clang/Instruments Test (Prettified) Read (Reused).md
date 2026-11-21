
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4037.87 | 0.0972467 | 4524.19ms | 183677 | 2560 | 4.5561e+06 | 43381.3 | 0.169344 | 0.612766 | 1(Win) | true |
| Jsonifier | 2490.07 | 0.152962 | 7302.86ms | 183677 | 160 | 1.85257e+06 | 70346.7 | 0.00122606 | 0.993892 | 2(Loss) | true |
| Glaze | 2358.99 | 0.172612 | 7692.98ms | 183677 | 320 | 5.25713e+06 | 74255.6 | 0.622236 | 1.04916 | 3(Loss) | true |
| simdjson (ondemand) | 1111.32 | 0.23243 | 8265.37ms | 183677 | 30 | 4.02661e+06 | 157622 | 0.0211098 | 2.22748 | 4(Loss) | true |
