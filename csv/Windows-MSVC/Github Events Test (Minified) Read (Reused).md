
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1544.92 | 0.19781 | 4014.7ms | 53331 | 1280 | 5.4282e+06 | 32921.1 | 0.0241997 | 1.60122 | 1(Win) | true |
| Glaze | 1460.34 | 0.130063 | 4225.03ms | 53331 | 2560 | 5.25292e+06 | 34827.8 | 0.0726262 | 1.6941 | 2(Loss) | true |
| Jsonifier (two-stage) | 1446.38 | 0.104762 | 4254.15ms | 53331 | 4890 | 6.63616e+06 | 35164 | 0.0536694 | 1.71007 | 3(Loss) | true |
| simdjson (ondemand) | 773.029 | 0.187256 | 7091.32ms | 53331 | 4890 | 7.42249e+07 | 65793.6 | 0.122412 | 3.20143 | 4(Loss) | true |
