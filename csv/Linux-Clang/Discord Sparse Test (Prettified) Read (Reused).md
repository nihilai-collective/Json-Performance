
----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 3580.88 | 0.102297 | 2536.8ms | 83958 | 4890 | 2.55848e+06 | 22360.1 | 0.0994508 | 0.690464 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 3574.82 | 0.113577 | 2552.42ms | 83958 | 2560 | 1.65666e+06 | 22397.9 | 0.581344 | 0.691702 | 1(Tie) | true |
