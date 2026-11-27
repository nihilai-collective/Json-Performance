
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3810.36 | 0.205946 | 4622.24ms | 183677 | 160 | 1.43419e+06 | 45971.6 | 0.177216 | 0.649402 | 1(Win) | true |
| Jsonifier (two-stage) | 3588.04 | 0.108033 | 4964.35ms | 183677 | 640 | 1.78029e+06 | 48819.9 | 0.0607924 | 0.689649 | 2(Loss) | true |
| Glaze | 2235.48 | 0.0500536 | 7864.96ms | 183677 | 4890 | 7.52223e+06 | 78358.1 | 0.390191 | 1.10713 | 3(Loss) | true |
| simdjson (ondemand) | 1080.81 | 0.138386 | 8375.07ms | 183677 | 160 | 8.04851e+06 | 162071 | 0.147487 | 2.29032 | 4(Loss) | true |
