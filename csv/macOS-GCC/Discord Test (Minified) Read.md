
----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6005.77 | 0.610866 | 970.134ms | 56369 | 1280 | 3.82688e+06 | 8951 | 2.19436 | 1(Win) | true |
| simdjson (stage-1) | 5616.08 | 0.240791 | 993.102ms | 56369 | 2560 | 1.35998e+06 | 9572.1 | 1.92119 | 2(Loss) | true |
