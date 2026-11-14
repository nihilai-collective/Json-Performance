
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1161.53 | 0.65087 | 5464.7ms | 65103 | 640 | 7.74662e+07 | 53453 | 0.686056 | 2.61535 | 1(Win) | true |
| Glaze | 1101.21 | 0.335407 | 5782.54ms | 65103 | 4890 | 1.74871e+08 | 56381 | 1.24278 | 2.7586 | 2(Loss) | true |
| Jsonifier | 1084.94 | 0.548582 | 5754.53ms | 65103 | 2560 | 2.52299e+08 | 57226.4 | 0.128082 | 2.80011 | 3(Loss) | true |
| simdjson (ondemand) | 900.269 | 0.16472 | 6971.82ms | 65103 | 1280 | 1.6518e+07 | 68965 | 0.263963 | 3.37488 | 4(Loss) | true |
