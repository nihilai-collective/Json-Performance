
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1813.28 | 0.425135 | 736.433ms | 11812 | 2560 | 1.78571e+06 | 6212.4 | 0.329457 | 1(Win) | true |
| Jsonifier (two-stage) | 1313.53 | 1.08226 | 1011.22ms | 11812 | 160 | 1.37832e+06 | 8576 | 0.865638 | 2(Loss) | true |
| simdjson (reflection) | 1068.22 | 0.28168 | 1143.56ms | 11812 | 1280 | 1.1294e+06 | 10545.4 | 0.051181 | 3(Loss) | true |
| Glaze | 1042.23 | 0.223247 | 1208.31ms | 11812 | 4890 | 2.84706e+06 | 10808.3 | 3.4436 | 4(Loss) | true |
| simdjson (ondemand) | 737.569 | 0.135372 | 1636.46ms | 11812 | 4890 | 2.09029e+06 | 15272.9 | 0.181126 | 5(Loss) | true |
