
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7442.76 | 0.151497 | 6092.87ms | 466906 | 640 | 5.25753e+06 | 59826.8 | 0.10776 | 1(Win) | true |
| Jsonifier | 6886.25 | 0.496776 | 6794.71ms | 466906 | 320 | 3.3019e+07 | 64661.6 | 1.15007 | 2(Loss) | true |
| Glaze | 1581.35 | 0.744836 | 7134.69ms | 466906 | 1280 | 5.63032e+09 | 281579 | 1.47759 | 3(Loss) | true |
