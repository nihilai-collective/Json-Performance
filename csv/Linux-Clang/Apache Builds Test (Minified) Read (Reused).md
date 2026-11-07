
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2490.86 | 0.0794324 | 4866.17ms | 94653 | 2560 | 2.12132e+06 | 36239.8 | 0.25498 | 0.993241 | 1(Win) | true |
| Jsonifier (two-stage) | 2192.9 | 0.0601586 | 5382.68ms | 94653 | 2560 | 1.56988e+06 | 41163.9 | 0.0709359 | 1.12829 | 2(Loss) | true |
| Glaze | 1911.8 | 0.062395 | 5905.29ms | 94653 | 4890 | 4.24418e+06 | 47216.4 | 0.364456 | 1.29428 | 3(Loss) | true |
| simdjson (ondemand) | 1442.8 | 0.0796005 | 7547.5ms | 94653 | 1280 | 3.17468e+06 | 62564.7 | 0.175169 | 1.71522 | 4(Loss) | true |
