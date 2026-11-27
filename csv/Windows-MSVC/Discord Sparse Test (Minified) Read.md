
----
### Discord Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1523.84 | 0.115062 | 3525.2ms | 56369 | 4890 | 8.05709e+06 | 35277.8 | 0.14659 | 1.99306 | 1(Win) | true |
| simdjson (ondemand) | 1432.06 | 0.187785 | 3755.07ms | 56369 | 4890 | 2.42989e+07 | 37538.6 | 0.0823601 | 2.121 | 2(Loss) | true |
