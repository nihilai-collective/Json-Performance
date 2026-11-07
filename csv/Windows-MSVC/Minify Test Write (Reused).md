
----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4097.98 | 0.428613 | 5750.31ms | 466906 | 80 | 1.73516e+07 | 108658 | 0.0528906 | 0.60398 | 1(Win) | true |
| Glaze | 1829.18 | 0.161973 | 6375.36ms | 466906 | 320 | 4.97486e+07 | 243429 | 0.1624 | 1.35335 | 2(Loss) | true |
| simdjson (ondemand) | 1405.83 | 0.170881 | 8124.78ms | 466906 | 160 | 4.68703e+07 | 316734 | 0.0859107 | 1.76085 | 3(Loss) | true |
