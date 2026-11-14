
----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 822.184 | 0.733632 | 7502.66ms | 4203059 | 40 | 5.11694e+10 | 4.87525e+06 | 1.89678 | 1(Win) | true |
| simdjson (ondemand) | 677.473 | 1.2208 | 8688.42ms | 4203059 | 30 | 1.56514e+11 | 5.91662e+06 | 0.737484 | 2(Loss) | true |
