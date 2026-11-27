
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (stage-1) | 5375.07 | 0.732907 | 1858.64ms | 108313 | 320 | 6.34804e+06 | 19217.5 | 0.288491 | 1(Win) | true |
| simdjson (stage-1) | 4347.8 | 0.826724 | 2273.75ms | 108313 | 320 | 1.23451e+07 | 23758.1 | 1.04651 | 2(Loss) | true |
