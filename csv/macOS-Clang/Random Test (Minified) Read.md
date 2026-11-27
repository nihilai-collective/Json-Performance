
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (stage-1) | 6261.14 | 0.68507 | 8051.44ms | 461466 | 30 | 6.95607e+06 | 70288.9 | 0.352885 | 1(Win) | true |
| Jsonifier (stage-1) | 6006.54 | 0.143232 | 7470.33ms | 461466 | 4890 | 5.3854e+07 | 73268.1 | 2.20893 | 2(Loss) | true |
