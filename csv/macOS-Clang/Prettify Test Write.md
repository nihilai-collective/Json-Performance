
----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3053.47 | 0.723112 | 5654.73ms | 699405 | 80 | 1.99604e+08 | 218441 | 1.43194 | 1(Win) | true |
| Glaze | 2143.01 | 0.265156 | 7766.08ms | 699405 | 1280 | 8.71805e+08 | 311246 | 0.683666 | 2(Loss) | true |
| simdjson (ondemand) | 1320.69 | 1.09322 | 6734.29ms | 767297 | 80 | 2.93514e+09 | 554068 | 0.159578 | 3(Loss) | true |
