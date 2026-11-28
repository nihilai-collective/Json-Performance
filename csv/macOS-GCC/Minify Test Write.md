
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7918.27 | 0.091592 | 5781.36ms | 466906 | 1280 | 3.39565e+06 | 56234 | 0.035553 | 1(Win) | true |
| simdjson (ondemand) | 7216.7 | 0.271346 | 6224ms | 466906 | 160 | 4.48486e+06 | 61700.8 | 0.325199 | 2(Loss) | true |
| Glaze | 1725.14 | 0.193884 | 6947.07ms | 466906 | 1280 | 3.20558e+08 | 258111 | 2.26378 | 3(Loss) | true |
