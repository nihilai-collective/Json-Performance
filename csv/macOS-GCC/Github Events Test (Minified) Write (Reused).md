
----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15177.6 | 0.36209 | 384.829ms | 58581 | 4890 | 868662 | 3680.9 | 1.58539 | 1(Win) | true |
| simdjson (reflection) | 10790.9 | 0.366495 | 551.699ms | 58581 | 4890 | 1.76055e+06 | 5177.27 | 0.393112 | 2(Loss) | true |
| Glaze | 3754.27 | 0.418634 | 1497.05ms | 58581 | 4890 | 1.89776e+07 | 14881 | 2.28588 | 3(Loss) | true |
