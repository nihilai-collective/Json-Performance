
----
### Twitter Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3302.23 | 0.13502 | 7628.17ms | 264040 | 2560 | 2.71369e+07 | 76254 | 0.171458 | 1(Win) | true |
| simdjson (ondemand) | 2383.16 | 0.166563 | 5469.62ms | 264040 | 320 | 9.91149e+06 | 105661 | 0.115419 | 2(Loss) | true |
