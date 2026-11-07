
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3220.49 | 0.137072 | 3385.51ms | 108313 | 640 | 1.23706e+06 | 32074.4 | 0.0457642 | 0.768143 | 1(Win) | true |
| Jsonifier (two-stage) | 2641.77 | 0.0618629 | 4077.24ms | 108313 | 4890 | 2.86115e+06 | 39100.8 | 0.0127402 | 0.936545 | 2(Loss) | true |
| Glaze | 1878.8 | 0.0622799 | 5649.14ms | 108313 | 2560 | 3.00149e+06 | 54979.5 | 0.000655069 | 1.31715 | 3(Loss) | true |
| simdjson (ondemand) | 737.416 | 0.045615 | 7255.14ms | 108313 | 1280 | 5.22589e+06 | 140077 | 0.00559711 | 3.35673 | 4(Loss) | true |
