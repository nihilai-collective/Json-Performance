
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2308.04 | 0.216327 | 2695.13ms | 53331 | 40 | 90897.8 | 22036.2 | 0.0845621 | 1.07132 | 1(Win) | true |
| Jsonifier | 2268.22 | 0.157956 | 2674.4ms | 53331 | 1280 | 1.60573e+06 | 22423 | 0.314829 | 1.09018 | 2(Loss) | true |
| Glaze | 1868.63 | 0.273148 | 3359.24ms | 53331 | 320 | 1.76872e+06 | 27218 | 0.77328 | 1.32369 | 3(Loss) | true |
| simdjson (ondemand) | 1130.37 | 0.280464 | 5030.44ms | 53331 | 80 | 1.27398e+06 | 44994.5 | 0.229079 | 2.18893 | 4(Loss) | true |
