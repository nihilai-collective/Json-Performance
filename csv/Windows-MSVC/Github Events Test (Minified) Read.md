
----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 765.811 | 0.416674 | 6929.31ms | 53331 | 160 | 1.22526e+07 | 66413.8 | 0.676469 | 3.23135 | 1(Win) | true |
| simdjson (ondemand) | 613.174 | 0.367407 | 8441.62ms | 53331 | 1280 | 1.18877e+08 | 82946.1 | 0.131848 | 4.03634 | 2(Loss) | true |
