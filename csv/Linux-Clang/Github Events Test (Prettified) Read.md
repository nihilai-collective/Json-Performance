
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2001.08 | 0.756092 | 3105.28ms | 65103 | 80 | 4.40265e+06 | 31026.8 | 0.283224 | 1.23611 | 1(Win) | true |
| Glaze | 1704.57 | 0.0983493 | 3683.33ms | 65103 | 2560 | 3.28517e+06 | 36424 | 0.231457 | 1.45136 | 2(Loss) | true |
| Jsonifier | 1449.28 | 0.279343 | 4256.95ms | 65103 | 1280 | 1.83307e+07 | 42839.8 | 0.0706658 | 1.70675 | 3(Loss) | true |
| simdjson (ondemand) | 1185.04 | 0.0576871 | 5400.12ms | 65103 | 4890 | 4.46686e+06 | 52392.3 | 0.34525 | 2.08798 | 4(Loss) | true |
