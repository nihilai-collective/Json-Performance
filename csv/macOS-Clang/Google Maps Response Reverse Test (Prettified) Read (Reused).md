
----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1347.08 | 0.039415 | 1845.9ms | 25388 | 30 | 1505.62 | 17973.6 | 0.116789 | 1(Win) | true |
| simdjson (ondemand) | 1173.98 | 0.113594 | 2083.64ms | 25388 | 2560 | 1.40502e+06 | 20623.7 | 0.16057 | 2(Loss) | true |
