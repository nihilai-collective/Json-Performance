
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1491.04 | 0.134357 | 202.792ms | 2632 | 320 | 1637.05 | 1683.44 | 0.167348 | 1.63165 | 1(Win) | true |
| Glaze | 1445.95 | 0.154756 | 217.79ms | 2632 | 320 | 2309.46 | 1735.94 | 0.305097 | 1.6848 | 2(Loss) | true |
| Jsonifier (two-stage) | 1336.45 | 0.383963 | 218.228ms | 2632 | 4890 | 254303 | 1878.16 | 0.0584435 | 1.8242 | 3(Loss) | true |
| simdjson (ondemand) | 866.288 | 0.1949 | 340.264ms | 2632 | 40 | 1275.64 | 2897.5 | 0.0862069 | 2.82448 | 4(Loss) | true |
