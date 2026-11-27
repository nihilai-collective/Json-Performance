
----
### Twitter Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4772.03 | 0.0616754 | 5470.13ms | 264040 | 4890 | 5.17926e+06 | 52767.6 | 0.0862969 | 1(Win) | true |
| simdjson (ondemand) | 3696.31 | 0.113211 | 7004.33ms | 264040 | 1280 | 7.61352e+06 | 68124.1 | 0.0991775 | 2(Loss) | true |
