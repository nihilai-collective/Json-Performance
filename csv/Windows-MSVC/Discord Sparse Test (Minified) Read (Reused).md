
----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2112.18 | 0.0939647 | 2944.81ms | 56369 | 640 | 366039 | 25451.2 | 0.286907 | 1.43759 | 1(Win) | true |
| simdjson (ondemand) | 1797.54 | 0.0443802 | 3402.33ms | 56369 | 4890 | 861409 | 29906.2 | 0.0413114 | 1.68952 | 2(Loss) | true |
