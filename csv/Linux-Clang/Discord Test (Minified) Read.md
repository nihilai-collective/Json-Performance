
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2252.36 | 0.107246 | 2393.45ms | 56369 | 2560 | 1.6773e+06 | 23867.3 | 0.0381011 | 1.09785 | 1(Win) | true |
| Jsonifier (two-stage) | 1881.88 | 0.053728 | 2861.45ms | 56369 | 4890 | 1.15188e+06 | 28566 | 0.0828085 | 1.31434 | 2(Loss) | true |
| Glaze | 1636.5 | 0.109461 | 3286.51ms | 56369 | 1280 | 1.65491e+06 | 32849.1 | 0.217255 | 1.51142 | 3(Loss) | true |
| simdjson (ondemand) | 878.297 | 0.0402522 | 6117.92ms | 56369 | 4890 | 2.96815e+06 | 61206.7 | 0.119881 | 2.81767 | 4(Loss) | true |
