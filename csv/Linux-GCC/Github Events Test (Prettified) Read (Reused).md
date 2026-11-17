
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2541.95 | 0.426767 | 2937.11ms | 65103 | 80 | 869243 | 24425 | 0.169977 | 0.972877 | 1(Win) | true |
| simdjson (reflection) | 2347.18 | 0.35902 | 3129.86ms | 65103 | 320 | 2.886e+06 | 26451.8 | 0.289112 | 1.05369 | 2(Loss) | true |
| Jsonifier | 2009.11 | 0.408815 | 3564.39ms | 65103 | 160 | 2.55369e+06 | 30902.7 | 0.0260967 | 1.23119 | 3(Loss) | true |
| Glaze | 1989.85 | 0.158472 | 3583.59ms | 65103 | 640 | 1.56476e+06 | 31201.9 | 0.0729102 | 1.24317 | 4(Loss) | true |
| simdjson (ondemand) | 1730.78 | 0.355908 | 4149.86ms | 65103 | 160 | 2.60803e+06 | 35872.3 | 0.0440954 | 1.4294 | 5(Loss) | true |
