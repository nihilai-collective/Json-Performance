
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (stage-1) | 1630.91 | 0.431235 | 83.508ms | 1313 | 40 | 438.487 | 767.775 | 0.0292969 | 1(Win) | true |
| simdjson (stage-1) DID NOT CONVERGE | 792.426 | 0.397218 | 156.488ms | 1313 | 4890 | 192654 | 1580.18 | 5.10882 | -(Loss) | false |
