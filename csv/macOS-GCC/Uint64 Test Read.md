
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 614.535 | 0.466751 | 195.002ms | 1213 | 4890 | 377493 | 1882.41 | 0.0418728 | 1(Win) | true |
| simdjson (ondemand) | 261.614 | 0.279238 | 439.188ms | 1213 | 2560 | 390288 | 4421.8 | 0.144947 | 2(Loss) | true |
