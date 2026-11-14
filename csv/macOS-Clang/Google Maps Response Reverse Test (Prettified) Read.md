
----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1217.32 | 0.293883 | 2097.91ms | 25388 | 640 | 2.18663e+06 | 19889.5 | 0.320325 | 1(Win) | true |
| simdjson (ondemand) | 991.747 | 0.305804 | 2399.62ms | 25388 | 1280 | 7.13431e+06 | 24413.4 | 0.159682 | 2(Loss) | true |
