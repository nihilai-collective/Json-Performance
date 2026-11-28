
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19976 | 0.486142 | 2226.23ms | 466906 | 160 | 1.87884e+06 | 22290.6 | 0.304998 | 0.123776 | 1(Win) | true |
| simdjson (ondemand) | 19510.4 | 0.113261 | 2290.72ms | 466906 | 2560 | 1.7105e+06 | 22822.5 | 0.262035 | 0.126716 | 2(Loss) | true |
| Glaze | 2624.47 | 0.0834521 | 8745.15ms | 466906 | 640 | 1.28301e+07 | 169663 | 0.081305 | 0.94319 | 3(Loss) | true |
