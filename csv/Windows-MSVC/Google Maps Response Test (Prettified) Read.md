
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2339.31 | 0.120356 | 1106.88ms | 25388 | 30 | 4655.17 | 10350 | 0.544523 | 1.05507 | 1(Win) | true |
| Jsonifier | 2239.77 | 0.15587 | 1122.82ms | 25388 | 30 | 8517.24 | 10810 | 0.123495 | 1.10211 | 2(Loss) | true |
| Glaze | 1415.5 | 0.177076 | 1766.53ms | 25388 | 2560 | 2.34852e+06 | 17104.8 | 0.120207 | 1.74602 | 3(Loss) | true |
| simdjson (ondemand) | 1250.69 | 0.117934 | 1987.81ms | 25388 | 4890 | 2.54883e+06 | 19358.8 | 0.171907 | 1.97658 | 4(Loss) | true |
