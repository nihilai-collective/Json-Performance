
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2680.97 | 0.0520774 | 3870.27ms | 108313 | 4890 | 1.96873e+06 | 38529.1 | 0.0981648 | 1(Win) | true |
| Jsonifier (two-stage) | 1767.16 | 0.0336196 | 5924.88ms | 108313 | 30 | 11585.5 | 58452.6 | 0.0402197 | 2(Loss) | true |
| Glaze | 1506.03 | 0.0474494 | 6953.49ms | 108313 | 4890 | 5.17922e+06 | 68587.9 | 0.0490333 | 3(Loss) | true |
| simdjson (ondemand) | 687.418 | 0.0879442 | 7821.63ms | 108313 | 640 | 1.11767e+07 | 150266 | 0.0477686 | 4(Loss) | true |
