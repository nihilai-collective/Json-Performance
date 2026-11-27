
----
### Canada Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4479.31 | 0.203972 | 5786.96ms | 2090234 | 40 | 3.29585e+07 | 445024 | 1.46197 | 1(Win) | true |
| simdjson (ondemand) | 3548.41 | 0.199837 | 7202.67ms | 2090234 | 40 | 5.04119e+07 | 561773 | 0.0954082 | 2(Loss) | true |
