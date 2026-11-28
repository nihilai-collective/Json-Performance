
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 999.313 | 0.188564 | 502.716ms | 4215 | 40 | 2301.28 | 4022.5 | 0.0207125 | 2.45518 | 1(Win) | true |
| Glaze | 788.57 | 0.177859 | 631.47ms | 4215 | 80 | 6575.95 | 5097.5 | 0.44335 | 3.12238 | 2(Loss) | true |
| simdjson (ondemand) | 534.362 | 0.100831 | 903.357ms | 4215 | 40 | 2301.28 | 7522.5 | 0.32023 | 4.61719 | 3(Loss) | true |
