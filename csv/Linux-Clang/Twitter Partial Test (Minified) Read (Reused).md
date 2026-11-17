
----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 10499.5 | 0.437565 | 4481.06ms | 466906 | 80 | 2.75486e+06 | 42409.4 | 0.495243 | 0.235641 | 1(Win) | true |
| Jsonifier | 10355.7 | 0.0996641 | 4440.3ms | 466906 | 1280 | 2.35066e+06 | 42998.3 | 0.0600293 | 0.238919 | 2(Loss) | true |
| simdjson (ondemand) | 7445 | 0.0631005 | 6042.75ms | 466906 | 4890 | 6.96473e+06 | 59808.8 | 0.428305 | 0.332335 | 3(Loss) | true |
| Glaze | 3367.78 | 0.484402 | 6977.91ms | 466906 | 40 | 1.64075e+07 | 132216 | 0.817838 | 0.734999 | 4(Loss) | true |
