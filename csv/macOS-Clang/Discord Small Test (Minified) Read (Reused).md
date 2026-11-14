
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1478.25 | 0.161318 | 337.976ms | 4857 | 30 | 766.53 | 3133.43 | 0.00531926 | 1(Win) | true |
| simdjson (ondemand) | 1181.73 | 0.0909502 | 410.429ms | 4857 | 1280 | 16267.3 | 3919.66 | 0.0215507 | 2(Loss) | true |
