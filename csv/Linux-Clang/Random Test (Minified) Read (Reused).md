
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1729.92 | 0.0615664 | 8550.88ms | 461466 | 1280 | 3.13996e+07 | 254398 | 0.0656549 | 1.431 | 1(Win) | true |
| Jsonifier (two-stage) | 1523.48 | 0.349916 | 9171.47ms | 461466 | 30 | 3.06519e+07 | 288871 | 1.5387 | 1.6249 | 2(Loss) | true |
| Glaze | 1303.26 | 0.173756 | 5240.75ms | 461466 | 80 | 2.75415e+07 | 337684 | 0.598099 | 1.89955 | 3(Loss) | true |
| simdjson (ondemand) | 969.906 | 0.0521243 | 6571.04ms | 461466 | 640 | 3.57998e+07 | 453743 | 0.52413 | 2.55244 | 4(Loss) | true |
