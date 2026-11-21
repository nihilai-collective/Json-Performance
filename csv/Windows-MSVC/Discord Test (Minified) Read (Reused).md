
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1835.55 | 0.169442 | 3492.16ms | 56369 | 1280 | 3.15211e+06 | 29287 | 0.735072 | 1.34756 | 1(Win) | true |
| Glaze | 1341.67 | 0.255009 | 4632.07ms | 56369 | 640 | 6.68162e+06 | 40067.8 | 0.633937 | 1.84403 | 2(Loss) | true |
| Jsonifier (two-stage) | 1287.92 | 0.223758 | 4715.65ms | 56369 | 640 | 5.58265e+06 | 41739.8 | 1.20162 | 1.92109 | 3(Loss) | true |
| simdjson (ondemand) | 1065.99 | 0.715321 | 5719.04ms | 56369 | 40 | 5.20523e+06 | 50430 | 0.211963 | 2.32149 | 4(Loss) | true |
