
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1768.57 | 0.0605969 | 10083.4ms | 728486 | 1280 | 7.25284e+07 | 392825 | 1.50411 | 1.39965 | 1(Win) | true |
| Jsonifier | 1532.86 | 0.152906 | 5863.87ms | 728486 | 40 | 1.92107e+07 | 453230 | 0.141875 | 1.61493 | 2(Loss) | true |
| Glaze | 1363.97 | 0.0709553 | 6466.6ms | 728486 | 160 | 2.08988e+07 | 509350 | 0.397299 | 1.81498 | 3(Loss) | true |
| simdjson (ondemand) | 1244.44 | 0.0745802 | 7161.16ms | 728486 | 320 | 5.5474e+07 | 558272 | 0.251588 | 1.98933 | 4(Loss) | true |
