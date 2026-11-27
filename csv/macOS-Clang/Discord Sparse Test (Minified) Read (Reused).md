
----
### Discord Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2420.31 | 0.0234362 | 2302.43ms | 56369 | 80 | 2167.71 | 22211 | 0.118887 | 1(Win) | true |
| simdjson (ondemand) | 1891.59 | 0.0683577 | 2999.25ms | 56369 | 4890 | 1.84549e+06 | 28419.3 | 0.0205872 | 2(Loss) | true |
