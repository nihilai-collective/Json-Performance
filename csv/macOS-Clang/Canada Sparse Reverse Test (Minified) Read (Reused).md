
----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3536.07 | 0.535065 | 7465.73ms | 2090234 | 40 | 3.63933e+08 | 563734 | 0.184313 | 1(Win) | true |
| simdjson (ondemand) | 2809.68 | 0.157574 | 9327.1ms | 2090234 | 160 | 1.9997e+08 | 709478 | 0.0666288 | 2(Loss) | true |
