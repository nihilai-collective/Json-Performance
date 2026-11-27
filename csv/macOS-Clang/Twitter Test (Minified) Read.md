
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1604.09 | 0.0649795 | 8086.96ms | 264040 | 2560 | 2.66363e+07 | 156979 | 0.0531861 | 1(Win) | true |
| simdjson (ondemand) | 1404.17 | 0.0731625 | 9196.45ms | 264040 | 2560 | 4.40676e+07 | 179329 | 0.0343396 | 2(Loss) | true |
