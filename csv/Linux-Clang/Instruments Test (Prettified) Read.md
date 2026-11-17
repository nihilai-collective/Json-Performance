
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3369.92 | 0.527186 | 5113.78ms | 183677 | 80 | 6.00742e+06 | 51979.9 | 0.0237648 | 0.734256 | 1(Win) | true |
| Jsonifier | 2146.41 | 0.152064 | 8215.79ms | 183677 | 320 | 4.92816e+06 | 81609.7 | 0.0215078 | 1.15309 | 2(Loss) | true |
| Glaze | 2117.39 | 0.0621455 | 8356.55ms | 183677 | 2560 | 6.76653e+06 | 82728.2 | 0.113951 | 1.1689 | 3(Loss) | true |
| simdjson (ondemand) | 1126.32 | 0.274876 | 8104.17ms | 183677 | 80 | 1.46201e+07 | 155523 | 0.706968 | 2.19775 | 4(Loss) | true |
