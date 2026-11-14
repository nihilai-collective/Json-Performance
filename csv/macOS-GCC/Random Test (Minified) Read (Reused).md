
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1207.14 | 0.24974 | 5193.12ms | 409725 | 30 | 1.96051e+07 | 323695 | 0.351852 | 1(Win) | true |
| simdjson (ondemand) | 706.767 | 0.0825783 | 8063.32ms | 409725 | 320 | 6.66983e+07 | 552862 | 0.0482089 | 2(Loss) | true |
