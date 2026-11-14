
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1378.06 | 0.0560424 | 6631.19ms | 94653 | 2560 | 3.44989e+06 | 65503.7 | 0.105616 | 1.79581 | 1(Win) | true |
| simdjson (ondemand) | 1222.29 | 0.138214 | 7414.69ms | 94653 | 320 | 3.33407e+06 | 73851.6 | 0.329842 | 2.02479 | 2(Loss) | true |
