
----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14269.8 | 0.29397 | 3154.64ms | 475954 | 1280 | 1.11921e+07 | 31808.8 | 1.26966 | 1(Win) | true |
| simdjson (reflection) | 11300.1 | 0.130974 | 4187.39ms | 475954 | 4890 | 1.35345e+07 | 40168.1 | 0.524734 | 2(Loss) | true |
| Glaze | 3742.23 | 0.969502 | 6559.3ms | 475954 | 40 | 5.53131e+07 | 121293 | 1.64474 | 3(Loss) | true |
