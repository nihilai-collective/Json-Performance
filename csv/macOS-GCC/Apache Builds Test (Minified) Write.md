
----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13318.6 | 1.02987 | 809.22ms | 94653 | 40 | 194886 | 6777.6 | 3.14024 | 1(Win) | true |
| simdjson (reflection) | 7542.01 | 0.492269 | 1184.65ms | 94653 | 4890 | 1.69749e+07 | 11968.7 | 2.69866 | 2(Loss) | true |
| Glaze | 4574.09 | 0.267505 | 1981.76ms | 94653 | 4890 | 1.3628e+07 | 19734.7 | 0.010294 | 3(Loss) | true |
