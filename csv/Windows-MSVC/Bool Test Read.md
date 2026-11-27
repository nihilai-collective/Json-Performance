
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 359.615 | 0.199776 | 253.654ms | 905 | 30 | 689.655 | 2400 | 0.139082 | 8.3923 | 1(Win) | true |
| simdjson (ondemand) | 177.483 | 0.0594314 | 493.143ms | 905 | 2560 | 21382.3 | 4862.85 | 0.10512 | 17.0644 | 2(Loss) | true |
