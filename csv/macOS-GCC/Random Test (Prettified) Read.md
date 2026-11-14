
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1269.86 | 0.230083 | 6995.96ms | 728486 | 40 | 6.3381e+07 | 547098 | 1.01467 | 1(Win) | true |
| Jsonifier (two-stage) | 1100.32 | 0.180713 | 8068.96ms | 728486 | 30 | 3.90576e+07 | 631398 | 0.279186 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1059 | 0.445397 | 8408.83ms | 728486 | 160 | 1.36606e+09 | 656035 | 2.67141 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1051.79 | 0.222317 | 8493.31ms | 728486 | 30 | 6.46926e+07 | 660531 | 0.130311 | 3(Tie) | true |
| simdjson (ondemand) | 904.562 | 1.04631 | 10057.6ms | 728486 | 40 | 2.58311e+09 | 768038 | 0.470513 | 5(Loss) | true |
