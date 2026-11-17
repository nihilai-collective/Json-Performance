
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1491.62 | 0.18345 | 4309.89ms | 53331 | 1280 | 5.00825e+06 | 34097.3 | 0.0697021 | 1.65842 | 1(Win) | true |
| Glaze | 1379.46 | 0.104251 | 4442.13ms | 53331 | 4890 | 7.22457e+06 | 36869.9 | 0.401209 | 1.79337 | 2(Loss) | true |
| Jsonifier (two-stage) | 1367.92 | 0.180656 | 4632.82ms | 53331 | 1280 | 5.77505e+06 | 37180.9 | 0.140558 | 1.8084 | 3(Loss) | true |
| simdjson (ondemand) | 745.726 | 0.472065 | 7723ms | 53331 | 80 | 8.29265e+06 | 68202.5 | 0.157371 | 3.3184 | 4(Loss) | true |
