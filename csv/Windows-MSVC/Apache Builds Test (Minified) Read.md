
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 706.648 | 0.514685 | 6644.31ms | 94653 | 1280 | 5.53293e+08 | 127741 | 0.0380552 | 3.50264 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 706.193 | 0.466128 | 6646.64ms | 94653 | 1280 | 4.54404e+08 | 127824 | 0.0213964 | 3.50508 | 1(Tie) | true |
