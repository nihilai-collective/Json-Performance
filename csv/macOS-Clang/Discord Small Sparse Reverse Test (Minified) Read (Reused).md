
----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2862.91 | 0.187352 | 166.505ms | 4857 | 2560 | 23522.2 | 1617.93 | 0.0179418 | 1(Win) | true |
| simdjson (ondemand) | 1576.17 | 0.0752101 | 300.209ms | 4857 | 1280 | 6253.06 | 2938.76 | 0.0427392 | 2(Loss) | true |
