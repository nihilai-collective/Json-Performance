
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 833.35 | 0.17714 | 8059.17ms | 2251027 | 80 | 1.66584e+09 | 2.57604e+06 | 0.0405385 | 1(Win) | true |
| Jsonifier (two-stage) | 739.772 | 0.140397 | 9073.1ms | 2251027 | 80 | 1.32791e+09 | 2.9019e+06 | 0.0985743 | 2(Loss) | true |
| Glaze | 599.186 | 0.215763 | 5439.95ms | 2251027 | 30 | 1.79273e+09 | 3.58277e+06 | 0.0646184 | 3(Loss) | true |
| simdjson (ondemand) | 537.179 | 0.217883 | 6009.34ms | 2251027 | 30 | 2.27453e+09 | 3.99633e+06 | 0.000175161 | 4(Loss) | true |
