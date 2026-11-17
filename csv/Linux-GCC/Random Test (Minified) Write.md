
----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14516.2 | 0.185797 | 3136.28ms | 461466 | 640 | 2.03064e+06 | 30317.1 | 0.322763 | 0.170382 | 1(Win) | true |
| simdjson (reflection) | 10088.8 | 0.272053 | 4338.35ms | 461466 | 160 | 2.25337e+06 | 43621.7 | 0.208035 | 0.245234 | 2(Loss) | true |
| Glaze | 3365.72 | 0.161958 | 6699.4ms | 461466 | 160 | 7.17548e+06 | 130756 | 0.252157 | 0.735044 | 3(Loss) | true |
