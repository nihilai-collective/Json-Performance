
----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 623.764 | 0.0868286 | 1844.46ms | 11812 | 2560 | 629466 | 18059.4 | 0.0166091 | 1(Win) | true |
| simdjson (ondemand) | 482.205 | 0.147442 | 2336ms | 11812 | 1280 | 1.51857e+06 | 23361 | 0.108847 | 2(Loss) | true |
