
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1745.07 | 0.0968211 | 8191.86ms | 461466 | 640 | 3.81568e+07 | 252189 | 0.0250737 | 1.41856 | 1(Win) | true |
| Jsonifier (two-stage) | 1455.75 | 0.0981323 | 9611.96ms | 461466 | 1280 | 1.12652e+08 | 302310 | 0.787276 | 1.70048 | 2(Loss) | true |
| Glaze | 1381.3 | 0.0671527 | 9858.02ms | 461466 | 320 | 1.46481e+07 | 318605 | 0.447233 | 1.7922 | 3(Loss) | true |
| simdjson (ondemand) | 965.606 | 0.123452 | 6583.79ms | 461466 | 160 | 5.06523e+07 | 455764 | 0.0866825 | 2.56378 | 4(Loss) | true |
