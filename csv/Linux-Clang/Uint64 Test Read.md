
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1729.09 | 0.081738 | 70.3644ms | 1213 | 80 | 23.9234 | 669.025 | 0.149248 | 1.37705 | 1(Win) | true |
| Glaze | 961.857 | 0.0486149 | 123.112ms | 1213 | 160 | 54.6965 | 1202.68 | 0.011951 | 2.51974 | 2(Loss) | true |
| simdjson (ondemand) | 313.399 | 0.174403 | 371.269ms | 1213 | 30 | 1243.25 | 3691.17 | 0.172782 | 7.84765 | 3(Loss) | true |
