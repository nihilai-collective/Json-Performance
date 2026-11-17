
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1895.83 | 0.458691 | 381.376ms | 5094 | 40 | 5526.1 | 2562.47 | 0.0523857 | 1(Win) | true |
| Jsonifier (two-stage) | 1355.15 | 0.328008 | 481.334ms | 5094 | 2560 | 353958 | 3584.85 | 0.367009 | 2(Loss) | true |
| Glaze | 861.51 | 0.383538 | 576.667ms | 5094 | 1280 | 598721 | 5638.96 | 0.101202 | 3(Loss) | true |
| simdjson (ondemand) | 716.24 | 0.226908 | 769.481ms | 5094 | 4890 | 1.15827e+06 | 6782.67 | 1.22237 | 4(Loss) | true |
