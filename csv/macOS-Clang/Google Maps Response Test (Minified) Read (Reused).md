
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2353.97 | 0.0387381 | 507.44ms | 11812 | 160 | 549.847 | 4785.45 | 0.0410266 | 1(Win) | true |
| Jsonifier (two-stage) | 1385.11 | 0.0165615 | 929.44ms | 11812 | 320 | 580.537 | 8132.8 | 7.68494e-05 | 2(Loss) | true |
| Glaze | 1113.84 | 0.256706 | 1030.94ms | 11812 | 1280 | 862743 | 10113.4 | 0.220738 | 3(Loss) | true |
| simdjson (ondemand) | 854.923 | 0.11987 | 1353.57ms | 11812 | 30 | 7484.04 | 13176.4 | 0.0417239 | 4(Loss) | true |
