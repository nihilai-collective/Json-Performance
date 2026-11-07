
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1484.13 | 0.159164 | 6024.84ms | 83958 | 640 | 4.71903e+06 | 53950 | 0.302028 | 1.66721 | 1(Win) | true |
| Jsonifier | 1446.02 | 0.0760278 | 5623.92ms | 83958 | 4890 | 8.66622e+06 | 55371.8 | 0.028722 | 1.71129 | 2(Loss) | true |
| Glaze | 1393.15 | 0.163776 | 5796.68ms | 83958 | 4890 | 4.33247e+07 | 57473 | 0.397718 | 1.77622 | 3(Loss) | true |
| simdjson (ondemand) | 1079.77 | 0.117964 | 7509.85ms | 83958 | 1280 | 9.79431e+06 | 74153.4 | 0.165136 | 2.29199 | 4(Loss) | true |
