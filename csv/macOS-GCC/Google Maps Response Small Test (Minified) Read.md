
----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1663.28 | 0.420322 | 256.709ms | 4390 | 2560 | 286553 | 2517.1 | 0.0198602 | 1(Win) | true |
| Jsonifier (two-stage) | 1213.73 | 0.238894 | 369.179ms | 4390 | 4890 | 332053 | 3449.4 | 0.167756 | 2(Loss) | true |
| simdjson (reflection) | 1067.99 | 0.143199 | 398.846ms | 4390 | 4890 | 154092 | 3920.1 | 0.201167 | 3(Loss) | true |
| Glaze | 1049.07 | 0.160785 | 405.821ms | 4390 | 2560 | 105403 | 3990.8 | 0.18009 | 4(Loss) | true |
| simdjson (ondemand) | 729.48 | 0.369598 | 565.074ms | 4390 | 640 | 287966 | 5739.2 | 0.0696476 | 5(Loss) | true |
