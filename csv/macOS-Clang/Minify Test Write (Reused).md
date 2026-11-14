
----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2273.52 | 0.110737 | 5024.67ms | 466906 | 1280 | 6.02085e+07 | 195853 | 0.52882 | 1(Win) | true |
| Glaze | 1751.54 | 0.101314 | 6546.52ms | 466906 | 640 | 4.2456e+07 | 254219 | 0.227037 | 2(Loss) | true |
| simdjson (ondemand) | 1262.92 | 0.0765552 | 9060.01ms | 466906 | 1280 | 9.32542e+07 | 352577 | 0.174554 | 3(Loss) | true |
