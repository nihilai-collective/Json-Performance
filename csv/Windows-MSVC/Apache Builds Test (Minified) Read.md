
----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 857.135 | 0.640417 | 5359.83ms | 94653 | 2560 | 1.16449e+09 | 105314 | 0.92474 | 3.54476 | 1(Win) | true |
| Glaze | 804.924 | 0.568791 | 5726.72ms | 94653 | 2560 | 1.04161e+09 | 112145 | 1.63254 | 3.77476 | 2(Loss) | true |
| Jsonifier (two-stage) | 765.139 | 0.75414 | 6019.86ms | 94653 | 2560 | 2.02643e+09 | 117976 | 0.467576 | 3.97111 | 3(Loss) | true |
| simdjson (ondemand) | 681.906 | 0.888456 | 6740.02ms | 94653 | 1280 | 1.77053e+09 | 132376 | 1.82796 | 4.45592 | 4(Loss) | true |
