
----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2983.73 | 0.267322 | 5726.65ms | 699405 | 1280 | 4.57109e+08 | 223547 | 0.412743 | 1(Win) | true |
| Glaze | 2233.17 | 0.285439 | 7694.11ms | 699405 | 1280 | 9.30359e+08 | 298680 | 1.35733 | 2(Loss) | true |
| simdjson (ondemand) | 1444.33 | 0.239764 | 6551.82ms | 767297 | 640 | 9.44366e+08 | 506636 | 2.20025 | 3(Loss) | true |
