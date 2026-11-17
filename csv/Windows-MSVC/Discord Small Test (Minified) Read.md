
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 963.321 | 0.217106 | 484.899ms | 4857 | 4890 | 532900 | 4808.36 | 0.215844 | 2.55175 | 1(Win) | true |
| Glaze | 822.005 | 0.280952 | 589.888ms | 4857 | 40 | 10025.6 | 5635 | 0.558824 | 2.99934 | 2(Loss) | true |
| Jsonifier (two-stage) | 793.49 | 0.250566 | 635.108ms | 4857 | 40 | 8557.69 | 5837.5 | 0.0998289 | 3.10319 | 3(Loss) | true |
| simdjson (ondemand) | 644.514 | 0.191237 | 733.996ms | 4857 | 4890 | 923690 | 7186.81 | 0.250844 | 3.82555 | 4(Loss) | true |
