
----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1652.45 | 0.107968 | 3862.2ms | 53331 | 4890 | 5.40009e+06 | 30778.8 | 0.268394 | 1.49674 | 1(Win) | true |
| Glaze | 1343.81 | 0.279591 | 4535.54ms | 53331 | 640 | 7.16657e+06 | 37848 | 0.0342771 | 1.84097 | 2(Loss) | true |
| Jsonifier (two-stage) | 1306.35 | 0.695588 | 4677.91ms | 53331 | 30 | 2.20023e+06 | 38933.3 | 0.2317 | 1.89355 | 3(Loss) | true |
| simdjson (ondemand) | 794.632 | 0.780146 | 7450.87ms | 53331 | 40 | 9.97331e+06 | 64005 | 0.0078125 | 3.11475 | 4(Loss) | true |
