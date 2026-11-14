
----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 580.45 | 0.708591 | 1884.04ms | 11812 | 160 | 3.02571e+06 | 19407 | 0.378291 | 1(Win) | true |
| simdjson (ondemand) | 486.403 | 0.286964 | 2316.47ms | 11812 | 1280 | 5.65352e+06 | 23159.4 | 0.0828407 | 2(Loss) | true |
