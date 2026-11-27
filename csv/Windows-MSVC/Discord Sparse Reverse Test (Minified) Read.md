
----
### Discord Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1264.76 | 0.305081 | 4256.06ms | 56369 | 640 | 1.07616e+07 | 42504.2 | 0.000367612 | 2.39895 | 1(Win) | true |
| simdjson (ondemand) | 947.347 | 0.101297 | 5677.7ms | 56369 | 4890 | 1.6157e+07 | 56745.5 | 0.0377223 | 3.20678 | 2(Loss) | true |
