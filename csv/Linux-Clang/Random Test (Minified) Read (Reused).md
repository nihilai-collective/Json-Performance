
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1766.82 | 0.0503943 | 8254.37ms | 461466 | 320 | 5.04208e+06 | 249085 | 0.00432852 | 2.86377 | 12.982 | 2.32283 | 0.0168196 | 0.00417747 | 1.26702e-05 | 1(Win) | true |
| Glaze | 1536.17 | 0.0459884 | 9232.85ms | 461466 | 1280 | 2.2218e+07 | 286484 | 0.267922 | 3.28982 | 15.2234 | 2.90401 | 0.0116302 | 0.00791946 | 5.68975e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1492.69 | 0.101953 | 9478.73ms | 461466 | 160 | 1.44565e+07 | 294829 | 0.0398122 | 3.38487 | 14.4747 | 2.58805 | 0.0224392 | 0.0267538 | 2.12096e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1025.01 | 0.108709 | 6355.82ms | 461466 | 640 | 1.39424e+08 | 429351 | 0.0121499 | 4.88076 | 21.1934 | 3.54764 | 0.00340877 | 0.0282894 | 5.22113e-05 | 4(Loss) | true |
