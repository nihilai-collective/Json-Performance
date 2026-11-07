
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3623.21 | 0.0787669 | 214.061ms | 7932 | 30 | 81.131 | 2087.8 | 0.113229 | 0.674466 | 1(Win) | true |
| Glaze | 2126.88 | 0.201178 | 362.212ms | 7932 | 2560 | 131063 | 3556.64 | 0.131023 | 1.15559 | 2(Loss) | true |
| Jsonifier | 2045.03 | 0.343366 | 366.612ms | 7932 | 640 | 103243 | 3698.99 | 0.461333 | 1.20179 | 3(Loss) | true |
| simdjson (ondemand) | 1102.66 | 0.133841 | 690.209ms | 7932 | 2560 | 215825 | 6860.28 | 0.135942 | 2.23652 | 4(Loss) | true |
