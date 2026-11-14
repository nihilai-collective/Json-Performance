
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1171.66 | 0.26957 | 8871.77ms | 108313 | 1280 | 7.22955e+07 | 88161.6 | 0.36932 | 1(Win) | true |
| simdjson (ondemand) | 1123.75 | 0.0916164 | 9354.92ms | 108313 | 640 | 4.53886e+06 | 91920 | 0.0383088 | 2(Loss) | true |
