
----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8268.09 | 0.282935 | 5377.37ms | 466906 | 4890 | 1.13535e+08 | 53854.8 | 0.277552 | 1(Win) | true |
| simdjson (stage-1) | 6561.07 | 0.270824 | 6951.6ms | 466906 | 2560 | 8.64815e+07 | 67866.4 | 0.536559 | 2(Loss) | true |
