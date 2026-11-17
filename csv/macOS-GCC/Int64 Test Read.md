
----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2721.58 | 0.584714 | 144.512ms | 3862 | 4890 | 306181 | 1353.29 | 0.0965279 | 1(Win) | true |
| simdjson (stage-1) | 1358.87 | 0.543769 | 277.944ms | 3862 | 1280 | 278039 | 2710.4 | 0.266351 | 2(Loss) | true |
