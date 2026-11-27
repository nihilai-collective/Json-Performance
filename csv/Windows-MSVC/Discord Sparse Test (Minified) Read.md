
----
### Discord Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1421.77 | 0.1769 | 3817.43ms | 56369 | 1280 | 5.72646e+06 | 37810.3 | 0.621226 | 1.73976 | 1(Win) | true |
| simdjson (ondemand) | 1358.59 | 0.142639 | 4026.69ms | 56369 | 2560 | 8.15491e+06 | 39568.6 | 0.000296162 | 1.82048 | 2(Loss) | true |
