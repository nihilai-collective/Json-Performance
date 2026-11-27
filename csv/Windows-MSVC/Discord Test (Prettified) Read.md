
----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1297.39 | 0.12525 | 6274.95ms | 83958 | 80 | 478000 | 61715 | 0.0728627 | 2.34136 | 1(Win) | true |
| simdjson (ondemand) | 1134.82 | 0.0972279 | 7108.09ms | 83958 | 2560 | 1.20473e+07 | 70555.9 | 0.147541 | 2.67715 | 2(Loss) | true |
