
----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 521.289 | 0.845212 | 811.432ms | 4390 | 2560 | 1.17962e+07 | 8031.3 | 1.62302 | 1(Win) | true |
| simdjson (ondemand) | 414.091 | 1.31867 | 1058.97ms | 4390 | 160 | 2.84401e+06 | 10110.4 | 0.397204 | 2(Loss) | true |
