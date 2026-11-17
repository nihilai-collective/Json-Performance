
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2510.65 | 0.0843366 | 3804.1ms | 65103 | 4890 | 2.12701e+06 | 24729.5 | 0.151289 | 2.01345 | 7.28399 | 1.14731 | 0.00606038 | 3.87996e-05 | 1.91014e-05 | 1(Win) | true |
| Jsonifier | 1946.7 | 0.146966 | 4547.84ms | 65103 | 2560 | 5.6244e+06 | 31893.5 | 0.312314 | 2.59906 | 7.85458 | 1.4294 | 0.00792926 | 6.16331e-05 | 3.43686e-05 | 2(Loss) | true |
| Glaze | 1923.93 | 0.0562332 | 4620.33ms | 65103 | 4890 | 1.61034e+06 | 32270.9 | 0.085611 | 2.62682 | 9.08225 | 1.68838 | 0.0181701 | 4.28203e-05 | 2.11463e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1366.69 | 0.0989659 | 5838.1ms | 65103 | 1280 | 2.58728e+06 | 45428.8 | 0.0385585 | 3.70009 | 11.2419 | 1.91534 | 0.00931278 | 6.92892e-05 | 4.11367e-05 | 4(Loss) | true |
