
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1933.25 | 0.0675828 | 4374.13ms | 83958 | 2560 | 2.00568e+06 | 41416.6 | 0.043932 | 1(Win) | true |
| simdjson (ondemand) | 1609.28 | 0.113218 | 5204.61ms | 83958 | 320 | 1.01541e+06 | 49754.3 | 0.000194706 | 2(Loss) | true |
