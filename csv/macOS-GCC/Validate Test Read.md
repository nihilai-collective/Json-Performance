
----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2244.07 | 0.210858 | 7124.62ms | 631514 | 80 | 2.56189e+07 | 268378 | 0.0357577 | 1(Win) | true |
| Glaze | 1736.35 | 0.274413 | 8453.72ms | 631514 | 1280 | 1.15961e+09 | 346853 | 0.797786 | 2(Loss) | true |
