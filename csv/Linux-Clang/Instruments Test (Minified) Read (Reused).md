
----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1857.03 | 0.0813584 | 5725.45ms | 108313 | 1280 | 2.62144e+06 | 55624.1 | 0.0448598 | 1.33257 | 1(Win) | true |
| simdjson (ondemand) | 1655.37 | 0.0417171 | 6368.6ms | 108313 | 4890 | 3.31367e+06 | 62400.2 | 0.140958 | 1.49493 | 2(Loss) | true |
