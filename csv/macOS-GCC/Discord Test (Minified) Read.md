
----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1737.71 | 0.559199 | 3178.66ms | 56369 | 160 | 4.78829e+06 | 30936 | 0.818646 | 1(Win) | true |
| Glaze | 1403.57 | 0.599894 | 4022.08ms | 56369 | 80 | 4.22333e+06 | 38300.8 | 0.0584502 | 2(Loss) | true |
| Jsonifier (two-stage) | 1285.72 | 0.223689 | 4566.59ms | 56369 | 80 | 699783 | 41811.2 | 1.44818 | 3(Loss) | true |
| simdjson (ondemand) | 972.968 | 0.322502 | 5862.88ms | 56369 | 40 | 1.27001e+06 | 55251.2 | 0.921959 | 4(Loss) | true |
| simdjson (reflection) | 610.527 | 1.61119 | 8054.05ms | 56369 | 40 | 8.05049e+07 | 88051.2 | 1.28671 | 5(Loss) | true |
