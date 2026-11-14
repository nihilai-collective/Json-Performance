
----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (stage-1) STATISTICAL TIE | 4759.28 | 0.282674 | 244.509ms | 11812 | 1280 | 57299.1 | 2366.91 | 0.181407 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4743.13 | 0.311376 | 240.047ms | 11812 | 1280 | 69999.8 | 2374.97 | 0.429305 | 1(Tie) | true |
