
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1810.14 | 2.94571 | 50.0669ms | 905 | 1280 | 252501 | 476.8 | 3.48178 | 1(Win) | true |
| Glaze | 1343.31 | 1.48484 | 68.4552ms | 905 | 2560 | 232994 | 642.5 | 0.0778816 | 2(Loss) | true |
| simdjson (reflection) | 827.969 | 1.31397 | 109.98ms | 905 | 640 | 120067 | 1042.4 | 0.610221 | 3(Loss) | true |
| simdjson (ondemand) | 404.175 | 0.393435 | 234.735ms | 905 | 2560 | 180694 | 2135.4 | 0.909513 | 4(Loss) | true |
