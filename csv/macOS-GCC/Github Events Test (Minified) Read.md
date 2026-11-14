
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1532.02 | 0.105111 | 3320.39ms | 53331 | 4890 | 5.95434e+06 | 33198.2 | 0.0908061 | 1(Win) | true |
| Glaze | 1374.03 | 0.182256 | 3753.72ms | 53331 | 1280 | 5.82564e+06 | 37015.6 | 0.143517 | 2(Loss) | true |
| Jsonifier (two-stage) | 1334.45 | 0.0862905 | 3902.47ms | 53331 | 4890 | 5.28916e+06 | 38113.3 | 0.435295 | 3(Loss) | true |
| simdjson (reflection) | 1124.31 | 0.365004 | 4542.88ms | 53331 | 160 | 4.36214e+06 | 45236.8 | 0.166513 | 4(Loss) | true |
| simdjson (ondemand) | 952.628 | 0.253221 | 5381.9ms | 53331 | 320 | 5.84875e+06 | 53389.6 | 0.157582 | 5(Loss) | true |
