
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1385.7 | 0.0762398 | 4435.7ms | 65103 | 4890 | 5.70603e+06 | 44805.5 | 0.424923 | 1.7855 | 1(Win) | true |
| simdjson (ondemand) | 1143.18 | 0.181409 | 5729.55ms | 65103 | 320 | 3.10627e+06 | 54310.6 | 0.0528737 | 2.16463 | 2(Loss) | true |
