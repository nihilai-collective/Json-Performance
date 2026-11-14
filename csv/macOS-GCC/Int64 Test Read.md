
----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2632.28 | 1.00959 | 140.449ms | 3862 | 2560 | 510842 | 1399.2 | 0.0142918 | 1(Win) | true |
| simdjson (stage-1) | 1249.01 | 1.05087 | 299.002ms | 3862 | 1280 | 1.22912e+06 | 2948.8 | 0.780619 | 2(Loss) | true |
