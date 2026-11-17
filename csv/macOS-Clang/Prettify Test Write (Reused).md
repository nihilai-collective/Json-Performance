
----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2792.56 | 0.504568 | 5815.86ms | 699405 | 640 | 9.29549e+08 | 238851 | 0.852514 | 1(Win) | true |
| Glaze | 2335.84 | 0.19766 | 7671.59ms | 699405 | 320 | 1.01943e+08 | 285552 | 1.48386 | 2(Loss) | true |
| simdjson (ondemand) | 1430.41 | 0.575579 | 6605.47ms | 767297 | 160 | 1.3872e+09 | 511568 | 0.853731 | 3(Loss) | true |
