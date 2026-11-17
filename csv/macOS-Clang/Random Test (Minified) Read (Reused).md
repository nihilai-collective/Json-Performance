
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1546.09 | 0.569511 | 9309.18ms | 461466 | 320 | 8.40934e+08 | 284645 | 0.0432939 | 1(Win) | true |
| Jsonifier (two-stage) | 1228.51 | 0.756619 | 6080.11ms | 461466 | 640 | 4.70175e+09 | 358230 | 0.603918 | 2(Loss) | true |
| Glaze | 959.73 | 0.536914 | 7334.64ms | 461466 | 30 | 1.8185e+08 | 458554 | 1.70062 | 3(Loss) | true |
| simdjson (ondemand) | 646.029 | 1.01999 | 9692.93ms | 461466 | 30 | 1.44839e+09 | 681221 | 2.37803 | 4(Loss) | true |
