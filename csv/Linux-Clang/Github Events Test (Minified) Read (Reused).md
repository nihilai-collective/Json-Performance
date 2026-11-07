
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2380.79 | 0.0697212 | 2605.84ms | 53331 | 4890 | 1.08481e+06 | 21362.8 | 0.061555 | 1.03861 | 1(Win) | true |
| Jsonifier | 2317.84 | 0.0943754 | 2705.88ms | 53331 | 4890 | 2.09709e+06 | 21943 | 0.223965 | 1.06688 | 2(Loss) | true |
| Glaze | 1856.88 | 0.0709135 | 3265.06ms | 53331 | 4890 | 1.84484e+06 | 27390.2 | 0.122819 | 1.33205 | 3(Loss) | true |
| simdjson (ondemand) | 1137.89 | 0.104303 | 4957.79ms | 53331 | 640 | 1.39102e+06 | 44697.2 | 0.167397 | 2.17437 | 4(Loss) | true |
