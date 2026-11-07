
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4190.57 | 0.0468301 | 4353.99ms | 183677 | 4890 | 1.8738e+06 | 41800.6 | 0.00923286 | 0.590431 | 1(Win) | true |
| Jsonifier | 2430.18 | 0.053232 | 7386.8ms | 183677 | 2560 | 3.76894e+06 | 72080.3 | 0.017894 | 1.01841 | 2(Loss) | true |
| Glaze | 2394.12 | 0.107931 | 7583.37ms | 183677 | 320 | 1.99555e+06 | 73165.9 | 0.0546061 | 1.03376 | 3(Loss) | true |
| simdjson (ondemand) | 1220.99 | 0.0569277 | 7421.99ms | 183677 | 2560 | 1.70754e+07 | 143464 | 0.00343686 | 2.0273 | 4(Loss) | true |
