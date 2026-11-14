
----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (stage-1) | 6860.91 | 0.249113 | 1178.75ms | 83958 | 1280 | 1.08184e+06 | 11670.2 | 0.528339 | 1(Win) | true |
| Jsonifier | 5886.2 | 0.25507 | 1363.96ms | 83958 | 1280 | 1.54094e+06 | 13602.8 | 0.162685 | 2(Loss) | true |
