
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1272.59 | 0.175529 | 8440.06ms | 108313 | 320 | 6.49573e+06 | 81169.1 | 0.0849373 | 1(Win) | true |
| simdjson (ondemand) | 1109.13 | 0.184734 | 9437.93ms | 108313 | 320 | 9.47189e+06 | 93131.5 | 0.00486855 | 2(Loss) | true |
