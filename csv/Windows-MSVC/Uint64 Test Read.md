
----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1758.85 | 0.170504 | 224.748ms | 3873 | 40 | 512.821 | 2100 | 0 | 1.71504 | 1(Win) | true |
| simdjson (stage-1) | 848.246 | 0.661341 | 447.399ms | 3873 | 160 | 132685 | 4354.38 | 0.0430787 | 3.55987 | 2(Loss) | true |
