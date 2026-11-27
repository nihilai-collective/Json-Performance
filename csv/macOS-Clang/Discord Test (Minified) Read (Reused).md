
----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1436.01 | 0.130903 | 3850.13ms | 56369 | 1280 | 3.07382e+06 | 37435.4 | 0.241306 | 1(Win) | true |
| simdjson (ondemand) | 1128.75 | 0.156889 | 4883.47ms | 56369 | 320 | 1.78658e+06 | 47625.9 | 0.00524241 | 2(Loss) | true |
