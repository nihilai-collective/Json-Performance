
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1475.71 | 0.77188 | 5458.96ms | 83958 | 40 | 7.01584e+06 | 54257.5 | 0.249724 | 1.67716 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1461.37 | 0.279974 | 5720.32ms | 83958 | 320 | 7.52987e+06 | 54790 | 0.333117 | 1.6933 | 1(Tie) | true |
| Glaze | 1325.05 | 0.870785 | 6198.25ms | 83958 | 30 | 8.30616e+06 | 60426.7 | 0.110448 | 1.86761 | 3(Loss) | true |
| simdjson (ondemand) | 1179.58 | 0.293279 | 6869.03ms | 83958 | 320 | 1.26819e+07 | 67879.1 | 0.350652 | 2.09816 | 4(Loss) | true |
