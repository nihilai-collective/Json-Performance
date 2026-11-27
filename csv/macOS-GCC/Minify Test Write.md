
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 6733.63 | 0.433049 | 6975.09ms | 466906 | 320 | 2.62412e+07 | 66127.2 | 0.446826 | 1(Win) | true |
| Jsonifier | 6636.42 | 0.151695 | 6751.74ms | 466906 | 4890 | 5.06574e+07 | 67095.8 | 0.618661 | 2(Loss) | true |
| Glaze | 1712.39 | 0.223466 | 6832.45ms | 466906 | 40 | 1.35063e+07 | 260032 | 0.1818 | 3(Loss) | true |
