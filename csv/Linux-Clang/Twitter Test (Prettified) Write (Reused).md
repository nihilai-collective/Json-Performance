
----
### Twitter Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15984.6 | 0.077652 | 4280.69ms | 716365 | 4890 | 5.38616e+06 | 42739.8 | 0.0860148 | 0.154778 | 1(Win) | true |
| Glaze | 5485.1 | 0.192924 | 6427.29ms | 716365 | 160 | 9.23833e+06 | 124552 | 0.0246072 | 0.451272 | 2(Loss) | true |
