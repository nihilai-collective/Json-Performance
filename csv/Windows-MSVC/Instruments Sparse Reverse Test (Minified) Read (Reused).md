
----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3167.59 | 0.154071 | 3295.2ms | 108313 | 4890 | 1.2344e+07 | 32610.1 | 0.169076 | 0.958723 | 1(Win) | true |
| simdjson (ondemand) | 2363.85 | 0.109885 | 4406.38ms | 108313 | 4890 | 1.12748e+07 | 43698 | 0.0312153 | 1.285 | 2(Loss) | true |
