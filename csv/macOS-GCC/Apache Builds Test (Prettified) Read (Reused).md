
----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2018.69 | 0.0591155 | 7911.68ms | 124597 | 2560 | 3.09971e+06 | 58862.5 | 0.0926745 | 1(Win) | true |
| Jsonifier (two-stage) | 1842.49 | 0.124422 | 8545.79ms | 124597 | 640 | 4.12076e+06 | 64491.6 | 0.0974719 | 2(Loss) | true |
| Glaze | 1833.77 | 0.0559847 | 8372.48ms | 124597 | 4890 | 6.4354e+06 | 64798.3 | 0.0474182 | 3(Loss) | true |
| simdjson (reflection) | 1471.8 | 0.119312 | 5127.02ms | 124597 | 640 | 5.93834e+06 | 80734.4 | 0.0564496 | 4(Loss) | true |
| simdjson (ondemand) | 1241.65 | 0.123855 | 6094.63ms | 124597 | 640 | 8.99129e+06 | 95699.2 | 0.0694322 | 5(Loss) | true |
