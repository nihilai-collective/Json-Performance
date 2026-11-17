
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2167.13 | 0.344785 | 576.764ms | 11812 | 1280 | 411133 | 5198.02 | 0.580159 | 1(Win) | true |
| Jsonifier (two-stage) | 1197.21 | 0.126452 | 1036.23ms | 11812 | 4890 | 692263 | 9409.24 | 0.140014 | 2(Loss) | true |
| Glaze | 880.627 | 0.744756 | 1235.18ms | 11812 | 320 | 2.9043e+06 | 12791.8 | 0.234925 | 3(Loss) | true |
| simdjson (ondemand) | 640.507 | 0.362592 | 1677.69ms | 11812 | 2560 | 1.04106e+07 | 17587.3 | 1.7976 | 4(Loss) | true |
