
----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4638.08 | 0.524255 | 9380.32ms | 7351818 | 80 | 5.02446e+09 | 1.51167e+06 | 0.253089 | 1(Win) | true |
| simdjson (ondemand) | 3547 | 0.336741 | 6182.12ms | 7351818 | 160 | 7.08891e+09 | 1.97667e+06 | 1.38485 | 2(Loss) | true |
