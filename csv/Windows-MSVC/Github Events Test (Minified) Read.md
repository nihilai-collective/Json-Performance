
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 955.349 | 0.211157 | 5431.27ms | 53331 | 40 | 505481 | 53237.5 | 0.0454147 | 3.17908 | 1(Win) | true |
| Glaze | 916.28 | 0.172757 | 5556.13ms | 53331 | 80 | 735639 | 55507.5 | 0.0675128 | 3.31536 | 2(Loss) | true |
| Jsonifier (two-stage) | 859.274 | 0.477261 | 5942.43ms | 53331 | 30 | 2.39403e+06 | 59190 | 0.02815 | 3.53445 | 3(Loss) | true |
| simdjson (ondemand) | 667.585 | 0.0986901 | 7689.03ms | 53331 | 160 | 904509 | 76185.6 | 0.148266 | 4.55155 | 4(Loss) | true |
