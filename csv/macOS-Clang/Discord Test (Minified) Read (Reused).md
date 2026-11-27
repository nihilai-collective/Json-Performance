
----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2913.38 | 0.107518 | 2057.68ms | 56369 | 320 | 125950 | 18452 | 0.315684 | 1(Win) | true |
| Jsonifier (two-stage) | 1930.36 | 0.112148 | 3119.38ms | 56369 | 1280 | 1.24853e+06 | 27848.5 | 0.272837 | 2(Loss) | true |
| Glaze | 1878.31 | 0.0789339 | 3017.47ms | 56369 | 2560 | 1.30651e+06 | 28620.2 | 0.0383153 | 3(Loss) | true |
| simdjson (ondemand) | 831.751 | 0.107074 | 6808.49ms | 56369 | 640 | 3.06505e+06 | 64631.9 | 0.282032 | 4(Loss) | true |
