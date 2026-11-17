
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2179.63 | 0.0384173 | 602.256ms | 11812 | 160 | 630.747 | 5168.21 | 0.23141 | 1(Win) | true |
| Jsonifier (two-stage) | 1233.1 | 0.195679 | 1074.28ms | 11812 | 40 | 12782 | 9135.35 | 0.356492 | 2(Loss) | true |
| Glaze | 1130.69 | 0.10453 | 1152.26ms | 11812 | 160 | 17352.3 | 9962.76 | 0.206156 | 3(Loss) | true |
| simdjson (ondemand) | 848.687 | 0.375787 | 1568.73ms | 11812 | 160 | 398066 | 13273.2 | 0.697629 | 4(Loss) | true |
