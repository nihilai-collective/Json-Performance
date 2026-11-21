
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1231.73 | 0.177473 | 9205.95ms | 461466 | 80 | 3.21663e+07 | 357291 | 0.145881 | 2.00978 | 1(Win) | true |
| Jsonifier (two-stage) | 1180.07 | 0.214567 | 9712.19ms | 461466 | 80 | 5.12252e+07 | 372935 | 0.124762 | 2.09777 | 2(Loss) | true |
| Glaze | 1057.24 | 0.227921 | 5335.9ms | 461466 | 40 | 3.60044e+07 | 416260 | 0.00493458 | 2.3415 | 3(Loss) | true |
| simdjson (ondemand) | 804.301 | 0.151947 | 7275.19ms | 461466 | 80 | 5.52987e+07 | 547169 | 0.142336 | 3.07798 | 4(Loss) | true |
