
----
### Package.json Corpus 0-512 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%200-512%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Package.json%20Corpus%200-512%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Package.json%20Corpus%200-512%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3497.4 | 0.0546383 | 43.6663ms | 1497 | 640 | 31.8366 | 408.203 | 0.101155 | 0.66329 | 1(Win) | true |
| simdjson (ondemand) | 3485.08 | 0.0574292 | 43.9051ms | 1497 | 640 | 35.4213 | 409.647 | 0.137886 | 0.666738 | 2(Loss) | true |
