
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1885.78 | 0.0398058 | 365.416ms | 6701 | 320 | 582.289 | 3388.82 | 0.0399132 | 1(Win) | true |
| simdjson (ondemand) | 1591.01 | 0.164999 | 419.561ms | 6701 | 40 | 1756.94 | 4016.68 | 0.103218 | 2(Loss) | true |
